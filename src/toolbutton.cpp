#include "toolbutton.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPalette>
#include <QPainter>
#include <QBitmap>

toolButton::toolButton(QString picName,QString text,QWidget *parent) :
    QWidget(parent)
{
    QPixmap pixmap(picName);
    QLabel *picLabel=new QLabel;
    picLabel->setPixmap(pixmap);
    picLabel->setFixedSize(pixmap.size());

    QLabel *textLabel=new QLabel(text);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(picLabel);
    mainLayout->addWidget(textLabel,0,Qt::AlignHCenter);
    setLayout(mainLayout);

    setBkPalette(0);
    setAutoFillBackground(true);
    setFixedHeight(80);
}

void toolButton::setBkPalette(int p)
{
    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(QColor(255,255,255,p)));
    setPalette(palette);
}
void toolButton::enterEvent(QEvent *)
{
    setBkPalette(30);
}
void toolButton::mousePressEvent(QMouseEvent *)
{
    setBkPalette(70);
}
void toolButton::mouseReleaseEvent(QMouseEvent *)
{
    setBkPalette(30);
    emit myToolClicked();
}
void toolButton::leaveEvent(QEvent *)
{
    setBkPalette(0);
}
void toolButton::paintEvent(QPaintEvent *)
{
    QBitmap bitmap(this->size());
    bitmap.fill();
    QPainter painter(&bitmap);
    painter.setRenderHints(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::black));
    painter.drawRoundedRect(bitmap.rect(),5,5);
    setMask(bitmap);
}
