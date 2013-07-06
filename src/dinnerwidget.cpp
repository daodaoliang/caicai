#include "dinnerwidget.h"
#include "ui_dinnerwidget.h"
#include <QProcess>
#include "sqlmanager.h"
#include "tabledelegate.h"
DinnerWidget::DinnerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DinnerWidget)
{
    ui->setupUi(this);
    startWx();
    m_model = new QSqlQueryModel(this);
    m_model->setQuery("select * from diningtable", *getSqlManager()->getdb());

    ui->listView->setModel(m_model);
    ui->listView->setItemDelegate(new TableDelegate);
}

DinnerWidget::~DinnerWidget()
{
    delete ui;
}

void DinnerWidget::startWx()
{

}
