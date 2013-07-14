#include "detailwidget.h"
#include "ui_detailwidget.h"
#include <QPainter>
#include <QSqlRecord>
DetailWidget::DetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailWidget)
{
    ui->setupUi(this);

    ui->tableView->setModel(&m_model);

}

DetailWidget::~DetailWidget()
{
    delete ui;
}

void DetailWidget::showDetail(const QString &sql)
{
    m_model.setQuery(sql, *getSqlManager()->getdb());
    m_model.setHeaderData(0, Qt::Horizontal, tr("菜名"));
    m_model.setHeaderData(1, Qt::Horizontal, tr("数量"));
    m_model.setHeaderData(2, Qt::Horizontal, tr("单价"));
    m_model.setHeaderData(3, Qt::Horizontal, tr("状态"));
    this->show();
    //设置总金额
    double money = 0;
    double price = 0;
    int count = 0;
    int flag = 0;
    for(int i = 0; i < m_model.rowCount(); i++)
    {
        if(m_model.record(i).value(3).toInt() == 1)
        {
            flag = -1;
        }
        else
        {
            flag = 1;
        }
        price = m_model.record(i).value(2).toDouble();
        count = m_model.record(i).value(1).toInt();
        money += price * count * flag;
    }
    ui->label_2->setText(QString::number(money, 'f', 2) + "元");
}


MyTableModel::MyTableModel(QWidget *obj) : QSqlQueryModel(obj)
{

}

QVariant MyTableModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    if (value.isValid() && role == Qt::DisplayRole)
    {
        if (item.column() == 2)
            return value.toString().append("元");
        else if (item.column() == 3)
            return value.toInt() == 1 ? "退菜" : "点菜";
    }
    return value;
}
