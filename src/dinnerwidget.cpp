#include "dinnerwidget.h"
#include "ui_dinnerwidget.h"
#include <QProcess>
#include "sqlmanager.h"
DinnerWidget::DinnerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DinnerWidget)
{
    ui->setupUi(this);
    startWx();
    m_model = new QSqlQueryModel(this);
    m_model->setQuery("select tablename, state, guestnumber, waiterid from diningtable", *getSqlManager()->getdb());
    m_model->setHeaderData(0, Qt::Horizontal, tr("��������"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("��ǰ״̬"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("�Ͳ�����"));
    m_model->setHeaderData(3, Qt::Horizontal, tr("����Ա���"));

    ui->tableView->setModel(m_model);
}

DinnerWidget::~DinnerWidget()
{
    delete ui;
}

void DinnerWidget::startWx()
{

}
