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
        QMessageBox::warning(NULL, tr("����"), "�ÿ���ע���Ա��");
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


    //�������֤�ŵ�2������10
    char tmp [16];
    memset(tmp,0,16);
    QByteArray arry = QByteArray::fromRawData(idCard.toLocal8Bit().data(),strlen(idCard.toLocal8Bit().data()));
    memcpy(tmp,QByteArray::fromHex(arry).data(),QByteArray::fromHex(arry).size());
    //getCardReader()->WriteCard(key,10,tmp,16);
    //qDebug()<<"-----------------------------"<<QString::fromLocal8Bit(QByteArray::fromHex(arry).data())<<arry<<QByteArray::fromHex(arry).size();
    //qDebug()<<tr("%1").arg(QByteArray::fromHex(arry).data());
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
    //�����Ա������Ϣ������2������8
    QString key = "ffffffffffff";
    QString name = ui->lineEdit_MemName->text();
    char tmp [16];
    memset(tmp,0,16);
    memcpy(tmp,name.toLocal8Bit().data(),qMin(16,(int)strlen(name.toLocal8Bit().data())));
    qDebug()<<"name len:"<<name.length();
    getCardReader()->WriteCard(key,8,tmp,16);
    //����绰��2������9
    QString phone = ui->lineEdit_Phone->text();
    memset(tmp,0,16);
    memcpy(tmp,phone.toLocal8Bit().data(),qMin(16,(int)strlen(phone.toLocal8Bit().data())));
    getCardReader()->WriteCard(key,9,tmp,16);
    //�����Աע��ʱ�䵽2������10
    QString starttime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    memset(tmp,0,16);
    memcpy(tmp,starttime.toLocal8Bit().data(),qMin(16,(int)strlen(starttime.toLocal8Bit().data())));
    getCardReader()->WriteCard(key,10,tmp,16);
    //�������֤��ǰ9λ��3����12��
    QString idCard = ui->lineEdit_IDCard->text();
    QString bidCard = idCard.left(9);
    memset(tmp,0,16);
    memcpy(tmp,bidCard.toLocal8Bit().data(),(int)strlen(bidCard.toLocal8Bit().data()));
    getCardReader()->WriteCard(key,12,tmp,16);
    //��9λ����6λ��3����13��
    QString aidCard = idCard.right(idCard.length() - 9);
    memset(tmp,0,16);
    memcpy(tmp,aidCard.toLocal8Bit().data(),(int)strlen(aidCard.toLocal8Bit().data()));
    getCardReader()->WriteCard(key,13,tmp,16);
    //�����Ա���͵�3����14��
    QString memtype = ui->lineEdit_MemType->text();
    memset(tmp,0,16);
    memcpy(tmp,memtype.toLocal8Bit().data(),(int)strlen(memtype.toLocal8Bit().data()));
    getCardReader()->WriteCard(key,14,tmp,16);
    //����ֵ���뵽4����16��
    QString shopid = ui->lineEdit_ShopID->text();
    memset(tmp,0,16);
    memcpy(tmp,shopid.toLocal8Bit().data(),(int)strlen(shopid.toLocal8Bit().data()));
    getCardReader()->WriteCard(key,16,tmp,16);
    return true;
}

void VipWidget::on_pushButton_OpenCard_clicked()
{
    QString key = "ffffffffffff";
    char rdata[16];
    QString cardID;
    memset(rdata,0,16);
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
    //memset(rdata,0,16);
    if(selectVipInfoByCardID(cardID))
    {
        //TODO:������ڸÿ���Ա,�б�����ʾ�û�Ա��Ϣ
    }
    qDebug()<<"read:"<<QString::fromLocal8Bit(rdata)<<"ID:"<<cardID;

}

void VipWidget::on_pushButton_Cancle_clicked()
{
    m_TableModel->revertAll();
}
