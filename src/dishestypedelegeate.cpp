#include "dishestypedelegeate.h"
#include <QPainter>
#include <QModelIndex>
#include <QDebug>
DishesTypeDelegeate::DishesTypeDelegeate(QObject *parent) :
    QItemDelegate(parent)
{
}

void DishesTypeDelegeate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //判断是否是选中状态
    if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());
    //画出图标
    painter->save();
    QRect newRect = option.rect;
    newRect.setX(newRect.x() + 15);
    newRect.setY(newRect.y() + 10);
    newRect.setHeight(newRect.height() - 20);
    newRect.setWidth(newRect.width() - 15);
    QPixmap iconImage(index.sibling(index.row(), 2).data().toString());
    painter->drawPixmap(newRect, iconImage);

    //画出文字


    //画出桌名
    QRect nameRect(option.rect.left(), option.rect.top() + option.rect.height() - 25, option.rect.width(), 25);
    QFont font;
    font.setPixelSize(20);
    painter->setFont(font);
    painter->drawText(nameRect, Qt::AlignCenter, index.sibling(index.row(), 1).data().toString());
//    //餐桌状态
//    if(index.sibling(index.row(), 2).data().toInt() == 1)
//    {
//        QRect busyRect;
//        busyRect.setLeft(option.rect.left() + (option.rect.width() - m_busyImage.width()) / 2);
//        busyRect.setTop((option.rect.top() + 25));
//        busyRect.setWidth(m_busyImage.width());
//        busyRect.setHeight(m_busyImage.height());
//        painter->drawPixmap(busyRect, m_busyImage);
//    }
////    //就餐人数

    painter->restore();
}


QSize DishesTypeDelegeate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(100,100);
}
