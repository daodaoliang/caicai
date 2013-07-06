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
    //����2
    //���ñ���ɫ͸��
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
    //����
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
        //����λ��
        move_point = event->globalPos() - this->pos();
    }
    event->ignore();


}

void PrinterWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //�������Ϊδ������
    mouse_press = false;
    event->ignore();
}

void PrinterWidget::mouseMoveEvent(QMouseEvent *event)
{
    //��������������
    if(mouse_press)
    {
        //��ȡλ��
        QPoint move_pos = event->globalPos();
        //�ƶ�������λ��
        this->move(move_pos - move_point);
    }
    event->ignore();
}

void PrinterWidget::on_pushButton_clicked()
{
    structCai temp;
    temp.caiName=tr("������������");
    temp.count=tr("2��");
    temp.price=tr("12Ԫ");
    temp.spMsg=tr("�����,�����,�����,�����,�����,�����");
    structDinner tempdata;
    tempdata.sCoName=tr("������Թ�˾");
    tempdata.sPartName=tr("������Թ�˾");
    tempdata.sZhuo=tr("324��");
    tempdata.time=QDateTime::currentDateTime().toString("yyyy/MM/DD--hh:mm:ss");
    tempdata.listCaicai.append(temp);
    tempdata.listCaicai.append(temp);
    tempdata.listCaicai.append(temp);
    tempdata.listCaicai.append(temp);
    if(getPrinterInstance()->slotWriteMsg(tempdata))
    {
        ui->textEdit->append(tr("��ӡ�ɹ�"));
    }
    else
    {
        ui->textEdit->append(tr("��ӡʧ��"));
    }
}
