#include "detailwidget.h"
#include "ui_detailwidget.h"
#include <QPainter>
#include <QSqlRecord>
#include <QItemDelegate>
#include <QStyleOptionProgressBarV2>
#include <QSqlError>
int m_nCurRow;
DetailWidget::DetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailWidget)
{
    ui->setupUi(this);

    ui->tableView->setModel(&m_model);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_nCurRow = -1;
    m_CurOrderid = "";
    m_CurOrderTime = "";
    m_CurMoney = 0;
    ui->pushButton->setVisible(false);
}

DetailWidget::~DetailWidget()
{
    delete ui;
}

void DetailWidget::showDetail(const QString &sql)
{
    m_CurOrderid = "";
    m_CurOrderTime = "";
    m_CurMoney = 0;
    m_model.setQuery(sql, *getSqlManager()->getdb());
    m_model.setHeaderData(0, Qt::Horizontal, tr("菜名"));
    m_model.setHeaderData(1, Qt::Horizontal, tr("数量"));
    m_model.setHeaderData(2, Qt::Horizontal, tr("单价"));
    m_model.setHeaderData(3, Qt::Horizontal, tr("状态"));
    m_model.setHeaderData(4, Qt::Horizontal, tr("订单号"));
    m_model.setHeaderData(5, Qt::Horizontal, tr("时间"));
    this->show();
    //ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
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
    //    if(item.row() == m_nCurRow && item.column() == 6)
    //    {
    //        return tr("已选");
    //    }
    //    if (role == Qt::CheckStateRole && item.column() == 6)
    //    {
    //        qDebug()<<"int -----------------------------------";
    //        return item.data(Qt::CheckStateRole).toInt() == Qt::Unchecked ? Qt::Checked : Qt::Unchecked;
    //    }

    return value;
}

//Qt::ItemFlags MyTableModel::flags(const QModelIndex &index) const
//{
//    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
//    if (index.column() == 6)
//        flags |= Qt::ItemIsUserCheckable;
//    else
//        flags |= Qt::ItemIsEditable;
//    return flags;

//}

void DetailWidget::on_tableView_clicked(const QModelIndex &index)
{
    qDebug() << index.row();
}
