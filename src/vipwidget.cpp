#include "vipwidget.h"
#include "ui_vipwidget.h"
#include "sqlmanager.h"
#include <QDebug>
#include <QSqlError>
#include <QTableView>
#include "readonlydelegate.h"
VipWidget::VipWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VipWidget)
{
    ui->setupUi(this);
    m_model = new QSqlTableModel(this,*getSqlManager()->getdb());
    m_model->setTable("member");
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->select();
    ui->tableView->setModel(m_model);
    ui->tableView->setItemDelegateForColumn(0,new readonlyDelegate(this));
    ui->tableView->setItemDelegateForColumn(1,new readonlyDelegate(this));
    ui->tableView->setItemDelegateForColumn(5,new readonlyDelegate(this));

}

VipWidget::~VipWidget()
{
    delete ui;
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
    int rowCount = m_model->rowCount();
    m_model->insertRow(rowCount);
    m_model->setData(m_model->index(rowCount,1),cardNum);
    m_model->setData(m_model->index(rowCount,2),memName);
    m_model->setData(m_model->index(rowCount,3),phone);
    m_model->setData(m_model->index(rowCount,4),idCard);
    m_model->setData(m_model->index(rowCount,5),QDateTime::currentDateTime());
    m_model->setData(m_model->index(rowCount,7),memType);
    m_model->setData(m_model->index(rowCount,8),shopid);
    //m_model->submitAll();
}

void VipWidget::on_pushButton_2_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    m_model->removeRow(curRow);
    //m_model->submitAll();
}

void VipWidget::on_pushButton_Save_clicked()
{
    m_model->submitAll();
}
