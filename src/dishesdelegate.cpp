#include "dishesdelegate.h"
#include <QPainter>
DishesDelegate::DishesDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void DishesDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //判断是否是选中状态
    if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());
    //画出图标
    painter->save();
    QRect newRect(option.rect.x(), option.rect.y(), 100, 100);

    newRect.setX(newRect.x() + 15);
    newRect.setY(newRect.y() + 15);
    newRect.setHeight(newRect.height() - 15);
    newRect.setWidth(newRect.width() - 15);
    QPixmap iconImage(index.sibling(index.row(), 3).data().toString());
    painter->drawPixmap(newRect, iconImage);

    //画出文字


    //画出桌名
    QRect nameRect(option.rect.left() + 100 + 5, option.rect.top() + 20, 200, 30);
    QFont font;
    font.setPixelSize(15);
    painter->setFont(font);
    painter->drawText(nameRect, Qt::AlignLeft, index.sibling(index.row(), 1).data().toString());

    //画出价格
    QRect priceRect(option.rect.left() + 105, option.rect.top() + 60, 200, 30);
    QString price = tr("%1元").arg(index.sibling(index.row(), 2).data().toDouble());
    painter->drawText(priceRect, Qt::AlignLeft, price);
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


QSize DishesDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(250,100);
}
