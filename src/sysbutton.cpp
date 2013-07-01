#include "sysbutton.h"
#include <QPainter>

sysButton::sysButton(QString picName,QString tipText,QWidget *parent) :
    QPushButton(parent)
{
    pixmap.load(":/img/sysButton/"+picName);
    setWindowOpacity(0);
    setFlat(true);
    btnWidth=pixmap.width()/4;
    btnHeight=pixmap.height();
    setFixedSize(btnWidth,btnHeight);
    setToolTip(tipText);
    status=NORMAL;
}
void sysButton::enterEvent(QEvent *)
{
    status=ENTER;
    update();
}
void sysButton::mousePressEvent(QMouseEvent *)
{
    status=PRESS;
    update();
}
void sysButton::mouseReleaseEvent(QMouseEvent *)
{
    status=ENTER;
    update();
    emit clicked();
}
void sysButton::leaveEvent(QEvent *)
{
    status=NORMAL;
    update();
}

void sysButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),pixmap.copy(btnWidth*status,0,btnWidth,btnHeight));
}
