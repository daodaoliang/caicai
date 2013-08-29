#include "functionwidget.h"
#include "ui_functionwidget.h"
#include <QDebug>
#include "dinnerwidget.h"
#include "vipwidget.h"
#include "checkwidget.h"
#include "orderwidget.h"
#include "tablewidget.h"
#include "statiswidget.h"
#include "carddetailwidget.h"
#include "membercustomwidget.h"
#include "backwidget.h"
#include "userwidget.h"
FunctionWidget::FunctionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionWidget)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(tableWidget());
    ui->stackedWidget->addWidget(vipWidget());
    ui->stackedWidget->addWidget(checkWidget());
    ui->stackedWidget->addWidget(statisWidget());
    ui->stackedWidget->addWidget(cardDetailWidget());
    ui->stackedWidget->addWidget(memberCustomWidgetInstance());
    ui->stackedWidget->addWidget(userWidget());
    ui->stackedWidget->addWidget(orderWidget());
    ui->stackedWidget->addWidget(backWidget());
}

FunctionWidget::~FunctionWidget()
{
    delete ui;
}

void FunctionWidget::changePage(int index)
{
    if(index >= ui->stackedWidget->count())
    {
        return;
    }

    ui->stackedWidget->setCurrentIndex(index);
}

bool FunctionWidget::winEvent(MSG *message, long *result)
{

}
