#include "tabledelegate.h"
#include <QDebug>
#include <QPainter>
TableDelegate::TableDelegate(QObject *parent) :
    QItemDelegate(parent), m_tableImage("://img/table.jpg"), m_busyImage("://img/s_32.png")
{
}

void TableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //QItemDelegate::paint(painter, option, index);

    //��������
    painter->save();
    QRect newRect = option.rect;
    newRect.setX(newRect.x() + 25);
    newRect.setY(newRect.y() + 25);
    newRect.setHeight(newRect.height() - 25);
    newRect.setWidth(newRect.width() - 25);
    painter->drawPixmap(newRect, m_tableImage);

    //��������
    QRect nameRect(option.rect.left(), option.rect.top() + option.rect.height() - 25, option.rect.width(), 25);
    QFont font;
    font.setPixelSize(20);
    painter->setFont(font);
    painter->drawText(nameRect, Qt::AlignCenter, index.sibling(index.row(), 1).data().toString());
    //����״̬

    if(index.sibling(index.row(), 2).data().toInt() == 1)
    {
        QRect busyRect;
        busyRect.setLeft((option.rect.width() - m_busyImage.width()) / 2);
        busyRect.setTop((option.rect.top() + 25));
        busyRect.setWidth(m_busyImage.width());
        busyRect.setHeight(m_busyImage.height());
        painter->drawPixmap(busyRect, m_busyImage);
    }
    //�Ͳ�����

    painter->restore();
}

QSize TableDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(150,150);
}
