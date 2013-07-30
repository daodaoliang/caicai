#include "statiswidget.h"
#include "ui_statiswidget.h"
#include "sqlmanager.h"
#include <qdebug.h>
StatisWidget::StatisWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisWidget)
{
    ui->setupUi(this);
    m_QueryModel = new QSqlQueryModel(this);
    m_TableModel = new QSqlTableModel(this,*getSqlManager()->getdb());
    ui->tableView->setModel(m_TableModel);
    m_TableModel->select();
    m_TableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

StatisWidget::~StatisWidget()
{
    delete ui;
}

void StatisWidget::on_but_Search_clicked()
{
    QString sql = "";
    //销售排名
    if(ui->box_SearchKind->currentIndex() == 0)
    {
        sql = tr("select dishes.dishesname, SUM(orderdetail.dishescount) as total, dishes.price from orderdetail " \
                 "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid " \
                 "group by dishes.dishesname, dishes.price " \
                 "order by total desc");
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("菜名"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("销售数量"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("单价"));

    }
    //点菜汇总
    if(ui->box_SearchKind->currentIndex() == 1 )
    {
    }
    //退菜
    if(ui->box_SearchKind->currentIndex() == 2)
    {

    }
    //套餐
    if(ui->box_SearchKind->currentIndex() == 3)
    {

    }
    //会员消费
    if(ui->box_SearchKind->currentIndex() == 4)
    {

    }
}
