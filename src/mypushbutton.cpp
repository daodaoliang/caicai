#include "mypushbutton.h"
#include <QPainter>
#include <QBitmap>

myPushButton::myPushButton(QString picName,QString tipText,QWidget *parent) :
    QPushButton(parent)
{
    setToolTip(tipText);
    setFlat(true);
    setWindowOpacity(0);
    pixmap.load(":/img/sysButton/"+picName);
    iconWidth=pixmap.width()/3;
    iconHeight=pixmap.height();

    setIcon(QIcon(pixmap.copy(0,0,iconWidth,iconHeight)));
    setIconSize(QSize(iconWidth,iconHeight));
}
void myPushButton::enterEvent(QEvent *)
{
    setWindowOpacity(0.1);
    setIcon(QIcon(pixmap.copy(iconWidth,0,iconWidth,iconHeight)));
}
void myPushButton::mousePressEvent(QMouseEvent *)
{
    setWindowOpacity(0.3);
    setIcon(QIcon(pixmap.copy(iconWidth*2,0,iconWidth,iconHeight)));
}
void myPushButton::mouseReleaseEvent(QMouseEvent *)
{
    setWindowOpacity(0.1);
    setIcon(QIcon(pixmap.copy(iconWidth,0,iconWidth,iconHeight)));
    emit clicked();
}
void myPushButton::leaveEvent(QEvent *)
{
    setWindowOpacity(0);
    setIcon(QIcon(pixmap.copy(0,0,iconWidth,iconHeight)));
}/*
void myPushButton::paintEvent(QPaintEvent *)
{
    QBitmap bitmap(this->size());
    bitmap.fill(Qt::white);
    QPainter painter(&bitmap);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::black));
    painter.setRenderHints(QPainter::Antialiasing,true);
    painter.drawRoundedRect(bitmap.rect(),5,5);
    setMask(bitmap);
    setIcon(QIcon(pixmap.copy(iconWidth*2,0,iconWidth,iconHeight)));

}*/
