#ifndef DISHESTYPEDELEGEATE_H
#define DISHESTYPEDELEGEATE_H
#include <QItemDelegate>
#include <QVector>
class DishesTypeDelegeate : public QItemDelegate
{
public:
    DishesTypeDelegeate(QObject *parent = 0);
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DISHESTYPEDELEGEATE_H
