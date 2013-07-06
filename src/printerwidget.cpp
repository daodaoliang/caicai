#include "printerwidget.h"
#include "ui_printerwidget.h"
#include <QPropertyAnimation>
#include <QMouseEvent>
#include "configerfileprocesser.h"
#include "printerprocesser.h"
PrinterWidget::PrinterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrinterWidget)
{
    ui->setupUi(this);
    //属性2
    //设置背景色透明
     QPalette palette;
     QColor color(190, 230, 250);
     palette.setBrush(this->backgroundRole(), color);
     this->setPalette(palette);
     this->setAutoFillBackground(true);
     getConfigerFileInstance()->createInstance();
     getPrinterInstance()->creatPrinterInstance();
}

PrinterWidget::~PrinterWidget()
{
    delete ui;
}

void PrinterWidget::EnterWidget(QWidget *data)
{
    //属性
    this->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    QPropertyAnimation *animation = new QPropertyAnimation(data, "windowOpacity");
    animation->setDuration(3000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

void PrinterWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        //窗口位置
        move_point = event->globalPos() - this->pos();
    }
    event->ignore();


}

void PrinterWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //设置鼠标为未被按下
    mouse_press = false;
    event->ignore();
}

void PrinterWidget::mouseMoveEvent(QMouseEvent *event)
{
    //若鼠标左键被按下
    if(mouse_press)
    {
        //获取位置
        QPoint move_pos = event->globalPos();
        //移动主窗体位置
        this->move(move_pos - move_point);
    }
    event->ignore();
}

void PrinterWidget::on_pushButton_clicked()
{
    QString tempdata=ui->textEdit->toPlainText().toAscii().toHex()  ;
    if(getPrinterInstance()->slotWriteMsg(tempdata))
    {
        ui->textEdit->append(tr("打印成功"));
    }
    else
    {
        ui->textEdit->append(tr("打印失败"));
    }
}
