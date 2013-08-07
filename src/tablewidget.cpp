#include "tablewidget.h"
#include "ui_tablewidget.h"
#include "tabledelegate.h"
#include "sqlmanager.h"
#include <QModelIndex>
#include "dinnertablebll.h"
#include <QMessageBox>
#include "functionwidget.h"
#include "orderwidget.h"
#include "dishesinfobll.h"
#include <QDebug>
#include "loginwidget.h"
#include <QMenu>
#include <QAction>
#include "dinnertablebll.h"
TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWidget)
{
    ui->setupUi(this);
    m_tableModel = new QSqlQueryModel(this);
    ui->tableWidget->setColumnWidth(0, 100);
    ui->tableWidget->setColumnWidth(1, 60);
    ui->tableWidget->setColumnWidth(2, 60);
    ui->tableWidget->setColumnWidth(3, 60);

    m_tableModel->setQuery("select * from diningtable", *getSqlManager()->getdb());
    ui->listView->setModel(m_tableModel);
    ui->listView->setItemDelegate(new TableDelegate);
    ui->toolButton_add->setEnabled(false);
    ui->toolButton_delete->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget->hideColumn(4);
    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);

    updateLoginInfo();
    ui->tableView->setModel(&m_loginModel);
}

TableWidget::~TableWidget()
{
    delete ui;
}

void TableWidget::resizeEvent(QResizeEvent *)
{
    updateView();
}

void TableWidget::showEvent(QShowEvent *)
{
    showDishesInfo(ui->listView->currentIndex().sibling(ui->listView->currentIndex().row(), 6).data().toString());
}

void TableWidget::on_listView_clicked(const QModelIndex &index)
{
    QString tableName = index.sibling(index.row(), 1).data().toString();
    int guestCount = index.sibling(index.row(), 3).data().toInt();
    ui->label_name->setText(tableName);
    ui->label_count->setText(tr("%1人").arg(guestCount));
    int state = index.sibling(index.row(), 2).data().toInt();
    enableFunction(state);
    showDishesInfo(ui->listView->currentIndex().sibling(ui->listView->currentIndex().row(), 6).data().toString());
    if(ui->listView->selectionModel()->selectedRows().count() == 2)
    {
        ui->toolButton_5->setEnabled(true);
    }
    else
    {
        ui->toolButton_5->setEnabled(false);
    }
    if(ui->listView->selectionModel()->selectedRows().count() == 1)
    {
        ui->toolButton_6->setEnabled(true);
    }
    else
    {
        ui->toolButton_6->setEnabled(false);
    }
}

void TableWidget::on_toolButton_clicked()
{
    updateView();
}

void TableWidget::showDishesInfo(const QString &orderId)
{
    QList<Dishes> dishesList = dishesInfoBllInstance()->getDishesInfo(orderId);
    clearDishesList();
    foreach(Dishes dish, dishesList)
    {
        if(dish.count > 0)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount() -1, 0, new QTableWidgetItem(dish.name));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() -1, 1, new QTableWidgetItem(tr("%1份").arg(dish.count)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() -1, 2, new QTableWidgetItem(tr("%1元").arg(dish.price, 0, 'f', 2)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() -1, 3, new QTableWidgetItem(dish.state == 0 ? "点菜" : "退菜"));
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(QString::number(dish.id)));
        }
    }
    double total = 0;
    for(int i = 0; i < dishesList.count(); i++)
    {
        total += dishesList.at(i).count * dishesList.at(i).price * (dishesList[i].state ? -1 : 1);
    }

    double rest = 0;
    QString text = tr("总计:<font size='6' color='red'><b>%1元</b></font>").arg(total - rest, 0, 'f', 2);
    ui->label_total->setText(text);
}

void TableWidget::updateView()
{
    QString tableId = ui->lineEdit->text();
    QModelIndex index = ui->listView->currentIndex();
    m_tableModel->setQuery(tr("select * from diningtable where tablename like '%%1%'").arg(tableId),
                           *getSqlManager()->getdb());
    ui->listView->setCurrentIndex(index);
}

void TableWidget::enableFunction(bool state)
{
    ui->stackedWidget->setCurrentIndex(!state);
    ui->toolButton_add->setEnabled(state);
    ui->toolButton_delete->setEnabled(state);
    ui->toolButton_4->setEnabled(state);
}

void TableWidget::clearDishesList()
{
    while(ui->tableWidget->rowCount() != 0)
    {
        ui->tableWidget->removeRow(0);
    }
}

void TableWidget::on_toolButton_3_clicked()
{
    int guestNumber = ui->lineEdit_2->text().toInt();
    bool result = dinnerTableBllInstance()->openTable(ui->listView->currentIndex().data().toString(), guestNumber);
    if(result)
    {
        QMessageBox::information(this, "提示", "开台成功");
        enableFunction(true);
        ui->label_count->setText(tr("%1人").arg(guestNumber));
        updateView();
    }
    else
    {
        QMessageBox::information(this, "提示", "开台失败");
    }
}

void TableWidget::on_toolButton_4_clicked()
{
    int state = ui->listView->currentIndex().sibling(ui->listView->currentIndex().row(), 2).data().toInt();

    if(!state)
    {
        return;
    }
    bool result = dinnerTableBllInstance()->closeTable(ui->listView->currentIndex().data().toString());
    if(result)
    {
        QMessageBox::information(this, "提示", "撤台成功");
        enableFunction(false);
        ui->lineEdit_2->clear();
        updateView();
        clearDishesList();
        ui->label_total->clear();
    }
    else
    {
        QMessageBox::information(this, "提示", "撤台失败");
    }
}

void TableWidget::on_toolButton_2_clicked()
{
    int result = m_addWidget.exec();
    if(result)
    {
        //执行插入语句
        QString sql = tr("insert into diningtable (id, tablename) values ('%1', '%2')")
                .arg(m_addWidget.newId())
                .arg(m_addWidget.newName());
        QSqlQuery *query = getSqlManager()->ExecQuery(sql);
        if(query)
        {
            if(query->numRowsAffected() == 1)
            {
                QMessageBox::information(this, "提示", "新建餐台成功");
                updateView();
                return;
            }
        }
        QMessageBox::information(this, "提示", "新建餐台失败");

    }
}

void TableWidget::on_toolButton_add_clicked()
{
    if(!ui->listView->currentIndex().isValid())
    {
        return;
    }
    if(ui->listView->currentIndex().sibling(ui->listView->currentIndex().row(), 2).data().toInt() == 1)
    {
        QString orderId = ui->listView->currentIndex().sibling(ui->listView->currentIndex().row(), 6).data().toString();
        QString tableId = ui->listView->currentIndex().data().toString();

        orderWidget()->setHandleType(orderId, tableId, 0);
        functionWidget()->changePage(4);
    }
}

void TableWidget::on_toolButton_delete_clicked()
{
    int row = ui->tableWidget->currentRow();


    if(row == -1)
    {
        QMessageBox::information(this, "提示","请选择要退的菜品");
        return;
    }
    LoginWidget w(this);
    w.setAuthType(LoginWidget::BackDish);
    if(!w.exec())
    {
        QMessageBox::information(this, "提示","验证失败");

        return;
    }
    int operatorId = w.authId();
    if(!m_countWidget.exec())
    {
        return;
    }

    int id = ui->tableWidget->item(row, 4)->text().toInt();
    QString tmpString = ui->tableWidget->item(row, 1)->text();
    int count = tmpString.left(tmpString.length() - 1).toInt();
    if(m_countWidget.getDishesCount() == 0)
    {
        QMessageBox::information(this, "提示","退菜数量不能为0");
        return;
    }
    if(count < m_countWidget.getDishesCount())
    {
        QMessageBox::information(this, "提示","退菜份数不能大于点菜份数");
        return;
    }
    count = m_countWidget.getDishesCount();
    QString orderId = ui->listView->currentIndex().sibling(ui->listView->currentIndex().row(), 6).data().toString();
    QString tableId = ui->listView->currentIndex().data().toString();

    bool result = dishesInfoBllInstance()->backDish(orderId, id, count, operatorId, 0, "", tableId);
    if(result)
    {
        QMessageBox::information(this, "提示", "退菜成功");
    }
    else
    {
        QMessageBox::information(this, "提示", "退菜失败");
    }
    showDishesInfo(orderId);
}


void TableWidget::on_toolButton_5_clicked()
{
    QString tableId1 = ui->listView->selectionModel()->selectedIndexes().at(0).data().toString();
    QString tableId2 = ui->listView->selectionModel()->selectedIndexes().at(1).data().toString();
    if(dinnerTableBllInstance()->combineTable(tableId1, tableId2))
    {
        updateView();
        QMessageBox::information(this, "提示", "并台成功");
    }
    else
    {
        QMessageBox::information(this, "提示", "并台失败");
    }
}

void TableWidget::on_toolButton_6_clicked()
{
    QString tableId = ui->listView->currentIndex().data().toString();
    if(dinnerTableBllInstance()->splitTable(tableId))
    {
        updateView();
        QMessageBox::information(this, "提示", "拆台成功");
    }
    else
    {
        QMessageBox::information(this, "提示", "拆台失败");
    }
}


void TableWidget::updateLoginInfo()
{
    //设置人员名称
    m_loginModel.setQuery("select userinfo.username, login.machineid from login"\
                          " LEFT JOIN userinfo ON"\
                          " userinfo.userid = login.userid", *getSqlManager()->getdb());
    m_loginModel.setHeaderData(0, Qt::Horizontal, "服务员");
    m_loginModel.setHeaderData(1, Qt::Horizontal, "点菜宝机器号");
}
