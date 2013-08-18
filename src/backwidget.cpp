#include "backwidget.h"
#include "ui_backwidget.h"

BackWidget::BackWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
}

BackWidget::~BackWidget()
{
    delete ui;
}

void BackWidget::showData(const QString &tableId)
{
    m_model.setHeaderData(0, Qt::Horizontal, "订单号");
    m_model.setHeaderData(1, Qt::Horizontal, "菜品名称");
    m_model.setHeaderData(2, Qt::Horizontal, "数量");
    m_model.setHeaderData(3, Qt::Horizontal, "单价");
    m_model.setHeaderData(4, Qt::Horizontal, "下单时间");
    m_model.setHeaderData(5, Qt::Horizontal, "支付方式");
    m_model.setHeaderData(6, Qt::Horizontal, "菜品ID");
    ui->tableView->hideColumn(6);

}

void BackWidget::on_tableView_clicked(const QModelIndex &index)
{

}

void BackWidget::on_pushButton_2_clicked()
{

}
