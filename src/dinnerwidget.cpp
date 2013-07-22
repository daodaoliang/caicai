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

void DinnerWidget::on_listView_doubleClicked(const QModelIndex &index)
{
    QString tableId = index.data().toString();
    //获取最后的时间
    QString sql = tr("select lastopentime from diningtable where id = '%1'").arg(tableId);
    QSqlQuery *query = getSqlManager()->ExecQuery(sql);
    QDateTime lastTime;
    if(query != NULL)
    {
        if(query->next())
        {
            lastTime = QDateTime::fromString(query->value(0).toString(), "yyyy-MM-ddThh:mm:ss");
            //获取菜品名称
            sql = tr("select dishes.dishesname, orderdetail.dishescount, dishes.price, orderdetail.dishestype from orderdetail " \
                     "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid where orderid in" \
                     "(select orderid from orderinfo where begintime >= '%1' and tableid = '%2')").arg(lastTime.toString("yyyy-MM-dd hh:mm:ss")).arg(tableId);
            qDebug() << sql;
            m_detailWidget.showDetail(sql);
        }
    }
}

void DinnerWidget::on_toolButton_2_clicked()
{
    if(ui->listView->currentIndex().isValid())
    {
        if(ui->listView->currentIndex().sibling(ui->listView->currentIndex().row(), 2).data().toInt() == 1)
        {
            //执行撤台操作
            QString sql = tr("update diningtable set state = 0 where id = '%1'").arg(ui->listView->currentIndex().data().toString());
            QSqlQuery *query = getSqlManager()->ExecQuery(sql);
            if(query->numRowsAffected() == 1)
            {
                updateData();
            }
            else
            {
                QMessageBox::information(this, "提示", "撤台失败");
            }
        }
        else
        {
            QMessageBox::information(this, "提示", "此台未开");
        }
    }
}

void DinnerWidget::on_toolButton_clicked()
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
                m_tableModel->setQuery("select * from diningtable", *getSqlManager()->getdb());
                return;
            }
        }
        QMessageBox::information(this, "提示", "新建餐台失败");

    }
}
