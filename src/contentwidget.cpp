#include "contentwidget.h"
#include <QPalette>

contentWidget::contentWidget(QWidget *parent) :
    QWidget(parent)
{
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(QColor(250,255,240,150)));
    setPalette(palette);
    setAutoFillBackground(true);
}
