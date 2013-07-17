#include "dinnerwidget.h"
#include "ui_dinnerwidget.h"
#include <QProcess>
#include "sqlmanager.h"
#include "tabledelegate.h"
#include <QMessageBox>
#include "dishestypedelegeate.h"
#include "dishesdelegate.h"
#include <QDebug>
DinnerWidget::DinnerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DinnerWidget)
{
    ui->setupUi(this);
    startWx();
    m_tableModel = new QSqlQueryModel(this);
    m_tableModel->setQuery("select * from diningtable", *getSqlManager()->getdb());
    ui->listView->setModel(m_tableModel);
    ui->listView->setItemDelegate(new TableDelegate);

}

DinnerWidget::~DinnerWidget()
{
    delete ui;
}

void DinnerWidget::updateData()
{
    m_tableModel->setQuery("select * from diningtable", *getSqlManager()->getdb());
}

void DinnerWidget::startWx()
{

}

//void DinnerWidget::on_toolButton_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(1);
//}

//void DinnerWidget::on_toolButton_2_clicked()
//{
//    DishesInfo info;
//    info.id = ui->leDishes->property("id").toInt();
//    info.count = ui->leDishesCount->text().toInt();
//    m_dishesList.append(info);
//}

//void DinnerWidget::on_toolButton_4_clicked()
//{
//    if(ui->lineEdit->text().isEmpty())
//    {
//        QMessageBox::information(this, "����", tr("������̨��"));
//        ui->lineEdit->setFocus();
//        return;
//    }
//    if(m_dishesList.count() == 0)
//    {
//        QMessageBox::information(this, "����", "�������û������Ʒ");
//        ui->leDishes->setFocus();
//        return;
//    }
//    bool result = orderHelperInstance()->createOrder(ui->lineEdit->text().toInt(), m_dishesList);
//    if(result)
//    {
//        QMessageBox::information(this, "��ʾ", "��������ɹ�!");
//    }
//    else
//    {
//        QMessageBox::information(this, "��ʾ", "��������ʧ��!");
//    }
//}

void DinnerWidget::on_toolButton_4_clicked()
{
//    ui->stackedWidget_2->setCurrentIndex(0);
}

void DinnerWidget::on_disheTypeList_doubleClicked(const QModelIndex &index)
{

}

void DinnerWidget::on_dishesList_doubleClicked(const QModelIndex &index)
{

}

void DinnerWidget::on_listView_doubleClicked(const QModelIndex &index)
{
    QString tableId = index.data().toString();
    //��ȡ����ʱ��
    QString sql = tr("select lastopentime from diningtable where id = '%1'").arg(tableId);
    QSqlQuery *query = getSqlManager()->ExecQuery(sql);
    QDateTime lastTime;
    if(query != NULL)
    {
        if(query->next())
        {
            lastTime = QDateTime::fromString(query->value(0).toString(), "yyyy-MM-ddThh:mm:ss");
            //��ȡ��Ʒ����
            sql = tr("select dishes.dishesname, orderdetail.dishescount, dishes.price, orderdetail.dishestype from orderdetail " \
                     "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid where orderid in" \
                     "(select orderid from orderinfo where begintime >= '%1' and tableid = '%2')").arg(lastTime.toString("yyyy-MM-dd hh:mm:ss")).arg(tableId);
            qDebug() << sql;
            m_detailWidget.showDetail(sql);
        }
    }
}
