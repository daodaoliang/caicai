#ifndef DISHESDELEGATE_H
#define DISHESDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QVector>
class DishesDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit DishesDelegate(QObject *parent = 0);
    
signals:
    
public slots:
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DISHESDELEGATE_H
