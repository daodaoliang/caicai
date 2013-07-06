#include "contentwidget.h"
#include <QPalette>
#include <QHBoxLayout>
#include <QVariant>
contentWidget::contentWidget(QWidget *parent) :
    QWidget(parent)
{
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(QColor(250,255,240,150)));
    setPalette(palette);
    setAutoFillBackground(true);
    QHBoxLayout *hLayout = new QHBoxLayout();
    m_function = new FunctionWidget();
    hLayout->addWidget(m_function);
    setLayout(hLayout);
}

void contentWidget::changePage()
{
    m_function->changePage(sender()->property("index").toInt());
}
