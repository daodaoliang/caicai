#include "mainwidget.h"
#include <QBitmap>
#include <QPainter>
#include <QBrush>

#include "titlewidget.h"
#include "toolwidget.h"
#include "statuswidget.h"
#include "contentwidget.h"
#include "skinwidget.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(850,600);
    setWindowFlags(Qt::FramelessWindowHint);
    bkPicName=":/img/skin/oldWood.jpg";

    titleWidget *titleW=new titleWidget;
    connect(titleW,SIGNAL(showMax()),this,SLOT(showMax()));
    connect(titleW,SIGNAL(showMin()),this,SLOT(showMin()));
    connect(titleW,SIGNAL(showSkin()),this,SLOT(showSkinWidget()));

    toolWidget *toolW=new toolWidget;
    toolW->setFocus();
    contentWidget *contentW=new contentWidget;
    statusWidget *statusW=new statusWidget;

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(titleW);
    mainLayout->addWidget(toolW);
    mainLayout->addWidget(contentW);
    contentW->setContentsMargins(1,5,1,0);
    mainLayout->addWidget(statusW);

    setLayout(mainLayout);
}

mainWidget::~mainWidget()
{
    
}

void mainWidget::paintEvent(QPaintEvent *)
{
    QBitmap bitmap(this->size());
    bitmap.fill();
    QPainter painter(&bitmap);
    painter.setBrush(QBrush(Qt::black));
    painter.drawRoundedRect(bitmap.rect(),5,5);
    setMask(bitmap);

    QPixmap pixmap(this->size());
    pixmap.fill();
    painter.end();
    painter.begin(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing,true);
    QBrush brush;
    brush.setStyle(Qt::TexturePattern);
    brush.setTextureImage(QImage(bkPicName));
    painter.setBrush(brush);
    painter.setPen(Qt::black);
    painter.drawRoundedRect(rect(),5,5);
    painter.end();
    painter.begin(this);
    painter.drawPixmap(this->rect(),pixmap);
}
void mainWidget::showMin()
{
    showMinimized();
}
void mainWidget::showMax()
{
    static bool isMax=false;
    if(isMax)
    {
        move(normalTopLeft);
        resize(850,600);
        isMax=false;
    }
    else
    {
        normalTopLeft=this->pos();
        setGeometry(QApplication::desktop()->availableGeometry());
        isMax=true;
    }
}

void mainWidget::showSkinWidget()
{
    skinWidget *skinW=new skinWidget(bkPicName);
    skinW->setAttribute(Qt::WA_DeleteOnClose);
    connect(skinW,SIGNAL(changeSkin(QString)),this,SLOT(setPicName(QString)));
    QPoint p=rect().topRight();
    p.setX(p.x()-150-350);
    p.setY(p.y()+30);
    skinW->move(this->mapToGlobal(p));
    skinW->show();
}
void mainWidget::setPicName(QString picName)
{
    bkPicName=picName;
    update();
}
