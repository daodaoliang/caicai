#include "statiswidget.h"
#include "ui_statiswidget.h"
#include "sqlmanager.h"
#include <QDebug>
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

    QString sql = tr("select userid, nickname from userinfo");
    QSqlQuery *query = getSqlManager()->ExecQuery(sql);
    if(query)
    {
        while(query->next())
        {
            ui->comboBox->insertItem(ui->comboBox->count(), query->value(1).toString(), query->value(0));
        }
    }
    ui->comboBox->setCurrentIndex(0);
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
        sql = tr("select * from orderdetail");
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
    }
    //点菜汇总
    if(ui->box_SearchKind->currentIndex() == 1 )
    {
        sql = tr("select dishes.dishesname, sum(orderdetail.dishescount) ,dishes.price from orderdetail "\
                 "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                 "where orderid in (select orderid from orderinfo where userid = %1) and dishestype = 0 "\
                 "group by dishes.dishesname, dishes.price").arg(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());
        m_TableModel->clear();
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0, Qt::Horizontal, "菜品名称");
        m_TableModel->setHeaderData(1, Qt::Horizontal, "所点次数");
        m_TableModel->setHeaderData(2, Qt::Horizontal, "菜品单价");
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
