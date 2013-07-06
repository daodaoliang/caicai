#include "dinnerwidget.h"
#include "ui_dinnerwidget.h"
#include <QProcess>
DinnerWidget::DinnerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DinnerWidget)
{
    ui->setupUi(this);
    startWx();
}

DinnerWidget::~DinnerWidget()
{
    delete ui;
}

void DinnerWidget::startWx()
{

}
