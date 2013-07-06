#include "contentwidget.h"
#include <QPalette>
#include <QHBoxLayout>
#include "functionwidget.h"
contentWidget::contentWidget(QWidget *parent) :
    QWidget(parent)
{
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(QColor(250,255,240,150)));
    setPalette(palette);
    setAutoFillBackground(true);
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(new FunctionWidget);
    setLayout(hLayout);
}
