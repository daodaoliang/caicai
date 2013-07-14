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
    
};

#endif // DISHESDELEGATE_H
