#include "vipwidget.h"
#include "ui_vipwidget.h"
#include "sqlmanager.h"
#include <QDebug>
#include <QSqlError>
#include <QTableView>
#include <QMessageBox>
#include "readonlydelegate.h"
#include "cardreadermanager.h"
VipWidget::VipWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VipWidget)
{
    ui->setupUi(this);
    m_QueryModel = new QSqlQueryModel(this);
    m_TableModel = new QSqlTableModel(this,*getSqlManager()->getdb());
    m_TableModel->setTable("member");
    m_TableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_TableModel->select();
    ui->tableView->setModel(m_TableModel);
    ui->tableView->setItemDelegateForColumn(0,new readonlyDelegate(this));
    ui->tableView->setItemDelegateForColumn(1,new readonlyDelegate(this));
    ui->tableView->setItemDelegateForColumn(5,new readonlyDelegate(this));

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
    //m_model->submitAll();
}

void VipWidget::on_pushButton_2_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    m_TableModel->removeRow(curRow);
    //m_model->submitAll();
}

void VipWidget::on_pushButton_Save_clicked()
{
    m_TableModel->submitAll();
    writeInfoToCard();
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
    //保存会员个人信息姓名到2扇区块8
    QString key = "ffffffffffff";
    QString name = ui->lineEdit_MemName->text();
    char tmp [16];
    memset(tmp,0,16);
    memcpy(tmp,name.toLocal8Bit().data(),qMin(16,(int)strlen(name.toLocal8Bit().data())));
    qDebug()<<"name len:"<<name.length();
    getCardReader()->WriteCard(key,8,tmp,16);
    //保存电话到2扇区块9
    QString phone = ui->lineEdit_Phone->text();
    memset(tmp,0,16);
    memcpy(tmp,phone.toLocal8Bit().data(),qMin(16,(int)strlen(phone.toLocal8Bit().data())));
    getCardReader()->WriteCard(key,9,tmp,16);
    //保存身份证号到2扇区块10
    return true;
}

void VipWidget::on_pushButton_OpenCard_clicked()
{
    QString key = "ffffffffffff";
    char rdata[16];
    QString cardID;
    if(getCardReader()->ReadCard(key,8,rdata,16,cardID))
    {
        ui->lineEdit_CardNum->setText(cardID);
    }
    if(selectVipInfoByCardID(cardID))
    {
        //TODO:如果存在该卡会员,列表单独显示该会员信息
    }
    qDebug()<<"read:"<<QString::fromLocal8Bit(rdata)<<"ID:"<<cardID;

}
