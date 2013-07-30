#include "statiswidget.h"
#include "ui_statiswidget.h"
#include "sqlmanager.h"
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
    //��������
    if(ui->box_SearchKind->currentIndex() == 0)
    {
        sql = tr("select * from orderdetail");
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
    }
    //��˻���
    if(ui->box_SearchKind->currentIndex() == 1 )
    {

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

    }
}
