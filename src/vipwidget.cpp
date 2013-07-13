#include "vipwidget.h"
#include "ui_vipwidget.h"
#include "sqlmanager.h"
#include <QDebug>
#include <QSqlError>
#include <QTableView>
#include <QMessageBox>
#include "readonlydelegate.h"
#include "cardreadermanager.h"
#include <QStringList>
#include <QTableWidget>
VipWidget::VipWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VipWidget)
{
    ui->setupUi(this);
    //记载数据库信息到图表
    m_QueryModel = new QSqlQueryModel(this);
    m_TableModel = new QSqlTableModel(this,*getSqlManager()->getdb());
    m_TableModel->setTable("member");
    m_TableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_TableModel->select();
    //显示的列名
    m_TableModel->setHeaderData(0,Qt::Horizontal,tr("会员编号"));
    m_TableModel->setHeaderData(1,Qt::Horizontal,tr("会员卡号"));
    m_TableModel->setHeaderData(2,Qt::Horizontal,tr("会员姓名"));
    m_TableModel->setHeaderData(3,Qt::Horizontal,tr("会员电话"));
    m_TableModel->setHeaderData(4,Qt::Horizontal,tr("身份证号"));
    m_TableModel->setHeaderData(5,Qt::Horizontal,tr("注册时间"));
    m_TableModel->setHeaderData(6,Qt::Horizontal,tr("到期时间"));
    m_TableModel->setHeaderData(7,Qt::Horizontal,tr("会员类型"));
    m_TableModel->setHeaderData(8,Qt::Horizontal,tr("所属分店"));
    m_TableModel->setHeaderData(9,Qt::Horizontal,tr("账户余额"));
    ui->tableView->setModel(m_TableModel);
    //设置列不可编辑
    ui->tableView->setItemDelegateForColumn(0,new readonlyDelegate(this));
    ui->tableView->setItemDelegateForColumn(1,new readonlyDelegate(this));
    ui->tableView->setItemDelegateForColumn(5,new readonlyDelegate(this));
    ui->tableView->setItemDelegateForColumn(9,new readonlyDelegate(this));
    //设置列不显示
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(6,true);
}

VipWidget::~VipWidget()
{
    delete ui;
    delete m_TableModel;
    delete m_QueryModel;
}

void VipWidget::on_pushButton_Add_clicked()
{
    QString shopid = ui->lineEdit_ShopID->text();
    QString memName = ui->lineEdit_MemName->text();
    QString memType = ui->lineEdit_MemType->text();
    QString idCard = ui->lineEdit_IDCard->text();
    QString phone = ui->lineEdit_Phone->text();
    QString cardNum = ui->lineEdit_CardNum->text();
    if(shopid.length()==0||memName.length()==0||memType.length()==0||idCard.length()==0||phone.length()==0||ui->lineEdit_CardNum->text().length()==0)
    {
        return;
    }
    if(selectVipInfoByCardID(cardNum))
    {
        QMessageBox::warning(NULL, tr("警告"), "该卡已注册会员！");
        return;
    }
    int rowCount = m_TableModel->rowCount();
    m_TableModel->insertRow(rowCount);
    m_TableModel->setData(m_TableModel->index(rowCount,1),cardNum);
    m_TableModel->setData(m_TableModel->index(rowCount,2),memName);
    m_TableModel->setData(m_TableModel->index(rowCount,3),phone);
    m_TableModel->setData(m_TableModel->index(rowCount,4),idCard);
    m_TableModel->setData(m_TableModel->index(rowCount,5),QDateTime::currentDateTime());
    m_TableModel->setData(m_TableModel->index(rowCount,7),memType);
    m_TableModel->setData(m_TableModel->index(rowCount,8),shopid);
    setTextEnable(false);
}

void VipWidget::on_pushButton_2_clicked()
{
    if(!ui->tableView->currentIndex().isValid())
    {
        qDebug()<<"请选择要删除的行";
        return;
    }
    int curRow = ui->tableView->currentIndex().row();
    m_TableModel->removeRow(curRow);
    resetText();
    setTextEnable(true);
    //m_model->submitAll();
}
//每次保存都会重新获取界面会员信息写到卡中
void VipWidget::on_pushButton_Save_clicked()
{
    if(!writeInfoToCard())
    {
        qDebug()<<"保存信息到卡失败";
        m_TableModel->revertAll();
        return;
    }
    m_TableModel->submitAll();
    resetText();
    setTextEnable(true);
}

bool VipWidget::selectVipInfoByCardID(const QString id)
{
    m_QueryModel->setQuery(tr("select count(*) from member where cardid = '%1'").arg(id),*getSqlManager()->getdb());
    while(m_QueryModel->query().next())
    {
        if(m_QueryModel->query().value(0).toInt() > 0 )
        {
            qDebug()<<"exist cardnum.....";
            return true;
        }
    }
    return false;
}

bool VipWidget::writeInfoToCard()
{
    //unsigned int type = 0x0004;
    //返回卡序列号地址
    //unsigned long snr;
    //unsigned char size;
    QString key = "ffffffffffff";
    char tmp [16];
    memset(tmp,0,16);
    //QString cardID = "";
    //保存会员个人信息姓名到2扇区块8
    QString name = ui->lineEdit_MemName->text();
    memcpy(tmp,name.toLocal8Bit().data(),qMin(16,(int)strlen(name.toLocal8Bit().data())));
    if(!getCardReader()->WriteCard(key,8,tmp,16))
    {
        qDebug()<<"会员姓名写卡失败";
        return false;
    }
    //保存电话到2扇区块9
    QString phone = ui->lineEdit_Phone->text();
    memset(tmp,0,16);
    memcpy(tmp,phone.toLocal8Bit().data(),qMin(16,(int)strlen(phone.toLocal8Bit().data())));
    if(!getCardReader()->WriteCard(key,9,tmp,16))
    {
        qDebug()<<"电话写卡失败";
        return false;
    }
    //保存会员注册时间到2扇区块10
    QString starttime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    memset(tmp,0,16);
    memcpy(tmp,starttime.toLocal8Bit().data(),qMin(16,(int)strlen(starttime.toLocal8Bit().data())));
    if(!getCardReader()->WriteCard(key,10,tmp,16))
    {
        qDebug()<<"注册时间写卡失败";
        return false;
    }
    //保存身份证号前9位到3扇区12块
    QString idCard = ui->lineEdit_IDCard->text();
    QString bidCard = idCard.left(9);
    memset(tmp,0,16);
    memcpy(tmp,bidCard.toLocal8Bit().data(),(int)strlen(bidCard.toLocal8Bit().data()));
    if(!getCardReader()->WriteCard(key,12,tmp,16))
    {
        qDebug()<<"前身份证写卡失败写卡失败";
        return false;
    }
    //后9位或者6位到3扇区13块
    QString aidCard = idCard.right(idCard.length() - 9);
    memset(tmp,0,16);
    memcpy(tmp,aidCard.toLocal8Bit().data(),(int)strlen(aidCard.toLocal8Bit().data()));
    if(!getCardReader()->WriteCard(key,13,tmp,16))
    {
        qDebug()<<"后身份证写卡写卡失败";
        return false;
    }
    //保存会员类型到3扇区14块
    QString memtype = ui->lineEdit_MemType->text();
    memset(tmp,0,16);
    memcpy(tmp,memtype.toLocal8Bit().data(),(int)strlen(memtype.toLocal8Bit().data()));
    if(!getCardReader()->WriteCard(key,14,tmp,16))
    {
        qDebug()<<"会员类型写卡失败";
        return false;
    }
    //保存分店编码到4扇区16块
    QString shopid = ui->lineEdit_ShopID->text();
    memset(tmp,0,16);
    memcpy(tmp,shopid.toLocal8Bit().data(),(int)strlen(shopid.toLocal8Bit().data()));
    if(!getCardReader()->WriteCard(key,16,tmp,16))
    {
        qDebug()<<"会员编号写卡失败";
        return false;
    }
    getCardReader()->Halt();
    return true;
}

void VipWidget::resetText()
{
    ui->lineEdit_CardNum->clear();
    ui->lineEdit_IDCard->clear();
    ui->lineEdit_MemName->clear();
    ui->lineEdit_MemType->clear();
    ui->lineEdit_Phone->clear();
    ui->lineEdit_ShopID->clear();
}

void VipWidget::setTextEnable(bool enable)
{
    //ui->lineEdit_CardNum->setEnabled(enable);
    ui->lineEdit_IDCard->setEnabled(enable);
    ui->lineEdit_MemName->setEnabled(enable);
    ui->lineEdit_MemType->setEnabled(enable);
    ui->lineEdit_Phone->setEnabled(enable);
    ui->lineEdit_ShopID->setEnabled(enable);
    ui->lineEdit_ShopID->setEnabled(enable);
}

void VipWidget::on_pushButton_OpenCard_clicked()
{
    unsigned int type = 0x0004;
    //返回卡序列号地址
    unsigned long snr;
    unsigned char size;
    QString key = "ffffffffffff";
    char rdata[16];
    QString cardID;
    memset(rdata,0,16);
    if(!getCardReader()->Reset(10))
    {
        qDebug()<<tr("reset false");
        return;
    }
    if(!getCardReader()->RequestCard(1,&type))
    {
        qDebug()<<tr("requestcard false");
        return;
    }
    if(!getCardReader()->AnticollCard(0,&snr))
    {
        qDebug()<<tr("anticollcard false");
        return;
    }
    if(!getCardReader()->SelectCard(snr,&size))
    {
        qDebug()<<tr("selectcard false");
        return;
    }
    cardID = QString::number(snr);
    //
    if(getCardReader()->ReadCard(key,8,rdata,16,cardID))
    {
        ui->lineEdit_CardNum->setText(cardID);
        ui->lineEdit_MemName->setText(QString::fromLocal8Bit(rdata));
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,9,rdata,16,cardID))
    {
        ui->lineEdit_Phone->setText(QString::fromLocal8Bit(rdata));
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,10,rdata,16,cardID))
    {
        qDebug()<<QString::fromLocal8Bit(rdata);
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,12,rdata,16,cardID))
    {
        ui->lineEdit_IDCard->setText(QString::fromLocal8Bit(rdata));
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,13,rdata,16,cardID))
    {
        ui->lineEdit_IDCard->setText(ui->lineEdit_IDCard->text()+(QString::fromLocal8Bit(rdata)));
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,14,rdata,16,cardID))
    {
        ui->lineEdit_MemType->setText(QString::fromLocal8Bit(rdata));
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,16,rdata,16,cardID))
    {
        ui->lineEdit_ShopID->setText(QString::fromLocal8Bit(rdata));
    }
    if(selectVipInfoByCardID(cardID))
    {
        //TODO:如果存在该卡会员,列表单独显示该会员信息
    }
    //getCardReader()->Halt();
    qDebug()<<"read:"<<QString::fromLocal8Bit(rdata)<<"ID:"<<cardID;
}

void VipWidget::on_pushButton_Cancle_clicked()
{
    m_TableModel->revertAll();
    resetText();
    setTextEnable(true);
}
