#include "orderwidget.h"
#include "ui_orderwidget.h"
#include "sqlmanager.h"
#include "dishestypedelegeate.h"
#include "dishesdelegate.h"
#include <QDebug>
#include <QMessageBox>
#include "backprinter.h"
#include "frontprinter.h"
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
    //初始化菜品model
    m_dishesModel = new QSqlQueryModel(this);
    ui->dishesList->setModel(m_dishesModel);
    ui->dishesList->setItemDelegate(new DishesDelegate);
    //初始化桌号
    QString sql = "select id, tablename from diningtable";
    QSqlQuery *query = getSqlManager()->ExecQuery(sql);
    if(query != NULL)
    {
        while(query->next())
        {
            ui->comboBox->insertItem(ui->comboBox->count(), query->value(1).toString(), query->value(0).toString());
        }
    }
    //初始化点菜退菜
    ui->comboBox_2->insertItem(0, "退菜", 1);
    ui->comboBox_2->insertItem(0, "点菜", 0);
    ui->comboBox_2->setCurrentIndex(0);
}

OrderWidget::~OrderWidget()
{
    delete ui;
}

void OrderWidget::showEvent(QShowEvent *)
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
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
        ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 0, new QTableWidgetItem(dishes));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 1, new QTableWidgetItem(QString::number(count)));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 2, new QTableWidgetItem(QString::number(price, 'f', 2) + "元"));
        DishesInfo dishesInfo;
        dishesInfo.name = dishes;
        dishesInfo.count = count;
        dishesInfo.id = index.data().toInt();
        dishesInfo.type = ui->comboBox_2->itemData(ui->comboBox_2->currentIndex()).toInt();
        dishesInfo.price = price;
        dishesInfo.dishType = dishType;
        qDebug() << "dish type" << dishType<<dishesInfo.name<<dishesInfo.count;
        m_dishesInfo.append(dishesInfo);
        showTotal();
    }
}

void OrderWidget::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
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
        total += m_dishesInfo.at(i).count * m_dishesInfo.at(i).price * (m_dishesInfo[i].type ? -1 : 1);
    }
    double rest = orderHelperInstance()->discount(m_dishesInfo);
    qDebug()<<"money"<<total<<rest;
    QString text = tr("总计:<font size='6' color='red'><b>%1元</b></font>").arg(total - rest, 0, 'f', 2);
    ui->label->setText(text);
}

void OrderWidget::on_toolButton_2_clicked()
{
    int index = ui->tableWidget_2->currentIndex().row();
    if(index != -1)
    {
        ui->tableWidget_2->removeRow(index);
        m_dishesInfo.removeAt(index);
        showTotal();
        ui->label->clear();
    }
}

void OrderWidget::on_toolButton_3_clicked()
{
    if(ui->tableWidget_2->rowCount() == 0)
    {
        return;
    }
    QString orderId;
    double price = 0;
    bool result = orderHelperInstance()->createOrder(ui->comboBox->itemData(ui->comboBox->currentIndex()).toString(),
                                                     m_dishesInfo,
                                                     "",
                                                     qApp->property("userId").toInt(), price, orderId);
    if(result)
    {
        result = getBackPrinter()->print(ui->comboBox->itemData(ui->comboBox->currentIndex()).toString(),
                                         m_dishesInfo, orderId, price);
       getFrontPrinter()->print(ui->comboBox->itemData(ui->comboBox->currentIndex()).toString(),
                                m_dishesInfo, orderId, price);
        if(result)
        {
            QMessageBox::information(this, "提示", "操作成功");
            m_dishesInfo.clear();
            while(ui->tableWidget_2->rowCount() > 0)
            {
                ui->tableWidget_2->removeRow(0);
            }
            ui->label->clear();
            return;
        }
    }
    QMessageBox::information(this, "提示", "操作失败");
}

void OrderWidget::on_comboBox_2_activated(int index)
{
    for(int i = 0; i < m_dishesInfo.count(); i++)
    {
        m_dishesInfo[i].type = ui->comboBox_2->itemData(index).toInt();
    }
    showTotal();
}
