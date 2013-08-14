#include "membercustomwidget.h"
#include "ui_membercustomwidget.h"
#include <QMessageBox>
#include "sqlmanager.h"
#include <QDebug>
#include "vipwidget.h"
MemberCustomWidget::MemberCustomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemberCustomWidget)
{
    ui->setupUi(this);

    ui->tableView->setModel(&m_model);
}

MemberCustomWidget::~MemberCustomWidget()
{
    delete ui;
}

void MemberCustomWidget::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "提示", "订单号不能为空");
        return;
    }
    QDate to = QDate::currentDate().addDays(1);
    QString sql = tr("SELECT orderdetail.orderid, orderdetail.handletime, orderinfo.tableid,  SUM(orderdetail.dishescount * dishes.price)  from orderdetail "\
                     "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid "\
                     "LEFT JOIN orderinfo on orderdetail.orderid  = orderinfo.orderid "\
                     "where orderdetail.dishestype = 0 and orderdetail.orderid like '%%1' and (handletime between '%2' and '%3')"\
                     "GROUP BY orderdetail.orderid, orderdetail.handletime, orderinfo.tableid").arg(ui->lineEdit->text())
            .arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(to.toString("yyyy-MM-dd"));

    m_model.setQuery(sql, *getSqlManager()->getdb());
    m_model.setHeaderData(0, Qt::Horizontal, "订单号");
    m_model.setHeaderData(1, Qt::Horizontal, "订单时间");
    m_model.setHeaderData(2, Qt::Horizontal, "桌号");
    m_model.setHeaderData(3, Qt::Horizontal, "总金额");
}

void MemberCustomWidget::on_pushButton_2_clicked()
{
    if(!ui->tableView->currentIndex().isValid())
    {
        QMessageBox::information(this, "提示", "请选择要支付的记录");
        return;
    }
    double payMoney = ui->tableView->model()->index(ui->tableView->currentIndex().row(), 3).data().toDouble();
    QString orderId = ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0).data().toString();
    QDateTime handleTime = ui->tableView->model()->index(ui->tableView->currentIndex().row(), 1).data().toDateTime();
    if(vipWidget()->payMoney(payMoney, orderId, handleTime).isEmpty())
    {
        QMessageBox::information(this, "提示", "支付失败");
    }
}
