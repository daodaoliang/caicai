#include "functionwidget.h"
#include "ui_functionwidget.h"

FunctionWidget::FunctionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionWidget)
{
    ui->setupUi(this);
}

FunctionWidget::~FunctionWidget()
{
    delete ui;
}
