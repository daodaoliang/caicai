#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QTreeWidgetItem>
#include <QDebug>
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWidget::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWidget::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWidget::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
}
