#include "titlewidget.h"
#include "sysbutton.h"
#include "mypushbutton.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QMouseEvent>

titleWidget::titleWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *versionText=new QLabel(tr("��Ĵ������ 1.0"));
    versionText->setStyleSheet("color: rgb(255, 255, 255);");
    btnSkin=new myPushButton("SkinButton.png",tr("����"));
    connect(btnSkin,SIGNAL(clicked()),this,SIGNAL(showSkin()));
    btnMenuBar=new sysButton("title_bar_menu.png",tr("���˵�"));
    btnMin=new sysButton("sys_button_min.png",tr("��С��"));
    connect(btnMin,SIGNAL(clicked()),this,SIGNAL(showMin()));
    btnMax=new sysButton("sys_button_max.png",tr("���"));
    connect(btnMax,SIGNAL(clicked()),this,SIGNAL(showMax()));
    btnClose=new sysButton("sys_button_close.png",tr("�ر�"));
    connect(btnClose,SIGNAL(clicked()),qApp,SLOT(quit()));

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->addWidget(versionText,0,Qt::AlignVCenter);
    versionText->setContentsMargins(5,0,0,0);
    mainLayout->addStretch();
    mainLayout->addWidget(btnSkin,0,Qt::AlignVCenter);
    btnSkin->setContentsMargins(0,0,5,0);
    mainLayout->addWidget(btnMenuBar);
    mainLayout->addWidget(btnMin);
    mainLayout->addWidget(btnMax);
    mainLayout->addWidget(btnClose);

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);
    setFixedHeight(25);
    isMove=false;
}

void titleWidget::mousePressEvent(QMouseEvent *e)
{
    //������ڰ�ť����  �����ƶ� ��������
    if(e->x()+170>=this->width())
        return;
    pressedPoint=e->pos();
    isMove=true;
}
void titleWidget::mouseMoveEvent(QMouseEvent *e)
{
    if( (e->buttons()&Qt::LeftButton) && isMove)
    {
        static QWidget* parWidget=this->parentWidget();
        QPoint nowParPoint=parWidget->pos();
        nowParPoint.setX(nowParPoint.x()+e->x()-pressedPoint.x());
        nowParPoint.setY(nowParPoint.y()+e->y()-pressedPoint.y());
        parWidget->move(nowParPoint);
    }
}
void titleWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(isMove)
        isMove=false;
}
void titleWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->x()+170>=this->width())
        return;
    emit showMax();
}
