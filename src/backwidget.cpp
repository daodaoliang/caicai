#include "backwidget.h"
#include "ui_backwidget.h"
#include "sqlmanager.h"
#include "vipwidget.h"
#include <QDebug>
BackWidget::BackWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

BackWidget::~BackWidget()
{
    delete ui;
}

void BackWidget::showData(const QString &tableId)
{
    QString sql = tr("select orderinfo.orderid, dishes.dishesname, orderdetail.dishescount, dishes.price,"\
                     "orderdetail.handletime, orderdetail.paytype, orderdetail.cardid,dishes.dishesid from orderdetail "\
                     "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                     "LEFT JOIN orderinfo on orderinfo.orderid = orderdetail.orderid "\
                     "where (handletime BETWEEN '%1' and '%2') and orderinfo.tableid = '%3'")
            .arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(QDate::currentDate().addDays(1).toString("yyyy-MM-dd"))
            .arg(tableId);

    m_model.setQuery(sql,*getSqlManager()->getdb());
    m_model.setHeaderData(0, Qt::Horizontal, "������");
    m_model.setHeaderData(1, Qt::Horizontal, "��Ʒ����");
    m_model.setHeaderData(2, Qt::Horizontal, "����");
    m_model.setHeaderData(3, Qt::Horizontal, "����");
    m_model.setHeaderData(4, Qt::Horizontal, "�µ�ʱ��");
    m_model.setHeaderData(5, Qt::Horizontal, "֧����ʽ");
    m_model.setHeaderData(6, Qt::Horizontal, "��Ա����");
    m_model.setHeaderData(7, Qt::Horizontal, "��ƷID");
    ui->tableView->hideColumn(7);
    qDebug()<<"�˲�"<<sql;
}

void BackWidget::on_tableView_clicked(const QModelIndex &index)
{

}

void BackWidget::on_pushButton_2_clicked()
{

}
