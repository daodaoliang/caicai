#include "orderwidget.h"
#include "ui_orderwidget.h"
#include "sqlmanager.h"
#include "dishestypedelegeate.h"
#include "dishesdelegate.h"
#include <QDebug>
#include <QMessageBox>
#include "backprinter.h"
#include "frontprinter.h"
#include "functionwidget.h"
OrderWidget::OrderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderWidget)
{
    ui->setupUi(this);
    //显示菜品类型
    m_dishesTypeModel = new QSqlQueryModel(this);
    m_dishesTypeModel->setQuery("select * from dishestype", *getSqlManager()->getdb());
    ui->disheTypeList->setModel(m_dishesTypeModel);
    ui->disheTypeList->setItemDelegate(new DishesTypeDelegeate);

    //设置不可编辑
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //初始化菜品model
    m_dishesModel = new QSqlQueryModel(this);
    ui->dishesList->setModel(m_dishesModel);
    ui->dishesList->setItemDelegate(new DishesDelegate);

}

OrderWidget::~OrderWidget()
{
    delete ui;
}

void OrderWidget::setHandleType(const QString &orderId, const QString &tableId, int state)
{
    m_orderId = orderId;
    m_tableId = tableId;
    m_dishState = state;
}

void OrderWidget::showEvent(QShowEvent *)
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void OrderWidget::hideEvent(QHideEvent *)
{
    m_dishState = 0;
    m_orderId.clear();
    m_tableId.clear();
}

void OrderWidget::on_disheTypeList_doubleClicked(const QModelIndex &index)
{
    ui->stackedWidget_2->setCurrentIndex(1);
    int dishesTypeId = index.data().toInt();
    QString sql = tr("select * from dishes where typeid = %1").arg(dishesTypeId);
    m_dishesModel->setQuery(sql, *getSqlManager()->getdb());
}

void OrderWidget::on_dishesList_doubleClicked(const QModelIndex &index)
{
    if(m_countWidget.exec())
    {
        qDebug() << m_countWidget.getDishesCount();
        QString dishes = index.sibling(index.row(), 1).data().toString();
        int count = m_countWidget.getDishesCount();
        double price = index.sibling(index.row(), 2).data().toDouble();
        int dishType = index.sibling(index.row(), 5).data().toInt();

        //如果有则合并，没有则添加
        if(m_dishesInfo.find(index.data().toInt()) != m_dishesInfo.end())
        {
            DishesInfo info = m_dishesInfo.value(index.data().toInt());
            info.count += count;
            m_dishesInfo[index.data().toInt()] = info;
        }
        else
        {
            DishesInfo dishesInfo;
            dishesInfo.name = dishes;
            dishesInfo.count = count;
            dishesInfo.id = index.data().toInt();
            dishesInfo.type = m_dishState;//ui->comboBox_2->itemData(ui->comboBox_2->currentIndex()).toInt();
            //退菜操作
            //            if(m_dishState == 1)
            //            {
            //                dishesInfo.count = dishesInfo.count * -1;
            //            }
            dishesInfo.price = price;
            dishesInfo.dishType = dishType;
            qDebug() << "dish type" << dishType<<dishesInfo.name<<dishesInfo.count;
            m_dishesInfo[index.data().toInt()] = dishesInfo;
        }
        int a = 0;
        qDebug() << ui->tableWidget_2->rowCount();
        //        while(a < ui->tableWidget_2->rowCount())
        //        {
        //            ui->tableWidget_2->removeRow(0);
        //            a++;
        //        }
        while(ui->tableWidget_2->rowCount() > 0)
        {
            ui->tableWidget_2->removeRow(0);
            a++;
        }
        qDebug()<<"remove count"<<a;
        for(int i = 0; i < m_dishesInfo.count(); i++)
        {
            ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
            ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 0, new QTableWidgetItem(m_dishesInfo.values()[i].name));
            ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 1, new QTableWidgetItem(QString::number(m_dishesInfo.values()[i].count)));
            ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 2, new QTableWidgetItem(QString::number(m_dishesInfo.values()[i].price, 'f', 2) + "元"));
            ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 3, new QTableWidgetItem(QString::number(m_dishesInfo.values()[i].id)));
            //            ui->tableWidget_2->insertRow(0);
            //            ui->tableWidget_2->setItem(0, 0, new QTableWidgetItem(m_dishesInfo.values()[i].name));
            //            ui->tableWidget_2->setItem(0, 1, new QTableWidgetItem(QString::number(m_dishesInfo.values()[i].count)));
            //            ui->tableWidget_2->setItem(0, 2, new QTableWidgetItem(QString::number(m_dishesInfo.values()[i].price, 'f', 2) + "元"));
            //            ui->tableWidget_2->setItem(0, 3, new QTableWidgetItem(QString::number(m_dishesInfo.values()[i].id)));
        }
        ui->tableWidget_2->hideColumn(3);
        showTotal();
    }
}

void OrderWidget::on_toolButton_clicked()
{
    if(ui->tableWidget_2->rowCount() == 0)
    {
        return;
    }
    double price = 0;
    QList<DishesInfo> tmpList = m_dishesInfo.values();
    bool result = orderHelperInstance()->createOrder(m_tableId,
                                                     tmpList,
                                                     "",
                                                     qApp->property("userId").toInt(), price, m_orderId, "", 1);
    if(result)
    {
        result = getBackPrinter()->print(m_tableId,
                                         m_dishesInfo.values(), m_orderId, price);
        getFrontPrinter()->print(m_tableId,
                                 m_dishesInfo.values(), m_orderId, price);
        qDebug() << "create order result" << result;
        if(result)
        {
            QMessageBox::information(this, "提示", "操作成功");
            m_dishesInfo.clear();
            while(ui->tableWidget_2->rowCount() > 0)
            {
                ui->tableWidget_2->removeRow(0);
            }
            ui->label->clear();
            functionWidget()->changePage(0);
            return;
        }
    }
    QMessageBox::information(this, "提示", "操作失败");
}

void OrderWidget::on_toolButton_5_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void OrderWidget::showTotal()
{
    double total = 0;
    for(int i = 0; i < m_dishesInfo.count(); i++)
    {
        total += m_dishesInfo.values().at(i).count * m_dishesInfo.values().at(i).price * (m_dishesInfo.values()[i].type ? -1 : 1);
        qDebug()<<"type"<<m_dishesInfo.values().at(i).dishType<<m_dishesInfo.values().at(i).name;
    }
    QList<DishesInfo> tmpList = m_dishesInfo.values();
    //double rest = orderHelperInstance()->discount(tmpList);
    double rest = 0;
    qDebug()<<"money"<<total<<rest;
    QString text = tr("总计:<font size='6' color='red'><b>%1元</b></font>").arg(total - rest, 0, 'f', 2);
    ui->label->setText(text);
}

void OrderWidget::on_toolButton_2_clicked()
{
    if(ui->tableWidget_2->currentIndex().row() != -1)
    {
        qDebug() << ui->tableWidget_2->currentRow();
        m_dishesInfo.remove(ui->tableWidget_2->item(ui->tableWidget_2->currentRow(), 3)->text().toInt());
        ui->tableWidget_2->removeRow(ui->tableWidget_2->currentIndex().row());
        showTotal();
    }
}

void OrderWidget::on_toolButton_3_clicked()
{
    if(ui->tableWidget_2->rowCount() == 0)
    {
        return;
    }
    double price = 0;
    QList<DishesInfo> tmpList = m_dishesInfo.values();
    bool result = orderHelperInstance()->createOrder(m_tableId,
                                                     tmpList,
                                                     "",
                                                     qApp->property("userId").toInt(), price, m_orderId);
    if(result)
    {
        result = getBackPrinter()->print(m_tableId,
                                         m_dishesInfo.values(), m_orderId, price);
        getFrontPrinter()->print(m_tableId,
                                 m_dishesInfo.values(), m_orderId, price);
        qDebug() << "create order result" << result;
        if(result)
        {
            QMessageBox::information(this, "提示", "操作成功");
            m_dishesInfo.clear();
            while(ui->tableWidget_2->rowCount() > 0)
            {
                ui->tableWidget_2->removeRow(0);
            }
            ui->label->clear();
            functionWidget()->changePage(0);
            return;
        }
    }
    QMessageBox::information(this, "提示", "操作失败");
}

