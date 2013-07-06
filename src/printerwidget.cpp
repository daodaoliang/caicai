#include "printerwidget.h"
#include "ui_printerwidget.h"
#include <QPropertyAnimation>
#include <QMouseEvent>
#include "configerfileprocesser.h"
#include "printerprocesser.h"
#include <QDateTime>
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
    structCai temp;
    temp.caiName=tr("西红柿炒鸡蛋");
    temp.count=tr("2份");
    temp.price=tr("12元");
    temp.spMsg=tr("多放糖,多放糖,多放糖,多放糖,多放糖,多放糖");
    structDinner tempdata;
    tempdata.sCoName=tr("宇宙测试公司");
    tempdata.sPartName=tr("宇宙测试公司");
    tempdata.sZhuo=tr("324桌");
    tempdata.time=QDateTime::currentDateTime().toString("yyyy/MM/DD--hh:mm:ss");
    tempdata.listCaicai.append(temp);
    tempdata.listCaicai.append(temp);
    tempdata.listCaicai.append(temp);
    tempdata.listCaicai.append(temp);
    if(getPrinterInstance()->slotWriteMsg(tempdata))
    {
        ui->textEdit->append(tr("打印成功"));
    }
    else
    {
        ui->textEdit->append(tr("打印失败"));
    }
}
