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
    m_TableModel->clear();
    //��������
    if(ui->box_SearchKind->currentIndex() == 0)
    {
        sql = tr("select dishes.dishesname, SUM(orderdetail.dishescount) as total, dishes.price from orderdetail " \
                 "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid " \
                 "group by dishes.dishesname, dishes.price " \
                 "order by total desc");
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("����"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("��������"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("����"));

    }
    //��˻���
    if(ui->box_SearchKind->currentIndex() == 1 )
    {
        sql = tr("select dishes.dishesname, sum(orderdetail.dishescount) ,dishes.price from orderdetail "\
                 "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                 "where orderid in (select orderid from orderinfo where userid = %1) and dishestype = 0 "\
                 "group by dishes.dishesname, dishes.price").arg(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());
        m_TableModel->clear();
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0, Qt::Horizontal, "��Ʒ����");
        m_TableModel->setHeaderData(1, Qt::Horizontal, "�������");
        m_TableModel->setHeaderData(2, Qt::Horizontal, "��Ʒ����");
    }
    //�˲�
    if(ui->box_SearchKind->currentIndex() == 2)
    {

    }
    //�ײ�
    if(ui->box_SearchKind->currentIndex() == 3)
    {

    }
    //��Ա����
    if(ui->box_SearchKind->currentIndex() == 4)
    {
        if(!ui->line_Vip->text().isEmpty())
        {
            sql = tr("SELECT cardid,orderid, SUM(orderdetail.dishescount * dishes.price)  as price , handletime from orderdetail "\
                    "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                    "where paytype = 1 and cardid = '%1' "\
                     "GROUP BY handletime").arg(ui->line_Vip->text());
        }
        else
        {
            sql = tr("SELECT cardid,orderid, SUM(orderdetail.dishescount * dishes.price)  as price , handletime from orderdetail "\
                    "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                    "where paytype = 1 "\
                     "GROUP BY handletime");
        }
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());

    }
}
