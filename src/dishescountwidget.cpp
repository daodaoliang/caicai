#include "dishescountwidget.h"
#include "ui_dishescountwidget.h"

DishesCountWidget::DishesCountWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DishesCountWidget)
{
    ui->setupUi(this);
}

DishesCountWidget::~DishesCountWidget()
{
    delete ui;
}

void DishesCountWidget::showEvent(QShowEvent *event)
{
    m_count = 0;
}

void DishesCountWidget::on_toolButton_clicked()
{
    m_count = m_count * 10 + 1;
    ui->lcdNumber->display (m_count);
}

void DishesCountWidget::on_toolButton_2_clicked()
{
    m_count = m_count * 10 + 2;
    ui->lcdNumber->display (m_count);
}

void DishesCountWidget::on_toolButton_3_clicked()
{
    m_count = m_count * 10 + 3;
    ui->lcdNumber->display (m_count);
}

void DishesCountWidget::on_toolButton_5_clicked()
{
    m_count = m_count * 10 + 4;
    ui->lcdNumber->display (m_count);
}

void DishesCountWidget::on_toolButton_6_clicked()
{
    m_count = m_count * 10 + 5;
    ui->lcdNumber->display (m_count);
}

void DishesCountWidget::on_toolButton_4_clicked()
{
    m_count = m_count * 10 + 6;
    ui->lcdNumber->display (m_count);
}

void DishesCountWidget::on_toolButton_8_clicked()
{
    m_count = m_count * 10 + 7;
    ui->lcdNumber->display (m_count);
}

void DishesCountWidget::on_toolButton_9_clicked()
{
    m_count = m_count * 10 + 8;
    ui->lcdNumber->display (m_count);
}

void DishesCountWidget::on_toolButton_7_clicked()
{
    m_count = m_count * 10 + 9;
    ui->lcdNumber->display (m_count);
}

void DishesCountWidget::on_toolButton_12_clicked()
{
    m_count = m_count * 10 + 0;
    ui->lcdNumber->display (m_count);
}

void DishesCountWidget::on_toolButton_11_clicked()
{
    m_count = m_count / 10;
    ui->lcdNumber->display (m_count);
}

void DishesCountWidget::on_toolButton_10_clicked()
{
    this->accept();
}
