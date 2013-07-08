#include "dinnerwidget.h"
#include "ui_dinnerwidget.h"
#include <QProcess>
#include "sqlmanager.h"
#include "tabledelegate.h"
#include <QMessageBox>
DinnerWidget::DinnerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DinnerWidget)
{
    ui->setupUi(this);
    startWx();
    m_model = new QSqlQueryModel(this);
    m_model->setQuery("select * from diningtable", *getSqlManager()->getdb());
    ui->listView->setModel(m_model);
    ui->listView->setItemDelegate(new TableDelegate);
}

DinnerWidget::~DinnerWidget()
{
    delete ui;
}

void DinnerWidget::updateData()
{
    m_model->setQuery("select * from diningtable", *getSqlManager()->getdb());
}

void DinnerWidget::startWx()
{

}

void DinnerWidget::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void DinnerWidget::on_toolButton_2_clicked()
{
    DishesInfo info;
    info.id = ui->leDishes->property("id").toInt();
    info.count = ui->leDishesCount->text().toInt();
    m_dishesList.append(info);
}

void DinnerWidget::on_toolButton_4_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "����", tr("������̨��"));
        ui->lineEdit->setFocus();
        return;
    }
    if(m_dishesList.count() == 0)
    {
        QMessageBox::information(this, "����", "�������û������Ʒ");
        ui->leDishes->setFocus();
        return;
    }
    bool result = orderHelperInstance()->createOrder(ui->lineEdit->text().toInt(), m_dishesList);
    if(result)
    {
        QMessageBox::information(this, "��ʾ", "��������ɹ�!");
    }
    else
    {
        QMessageBox::information(this, "��ʾ", "��������ʧ��!");
    }
}
