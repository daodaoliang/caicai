#include "orderwidget.h"
#include "ui_orderwidget.h"

OrderWidget::OrderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderWidget)
{
    ui->setupUi(this);
}

OrderWidget::~OrderWidget()
{
    delete ui;
}
