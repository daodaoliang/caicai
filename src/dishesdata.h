#ifndef DISHESDATA_H
#define DISHESDATA_H

#include <QObject>
#include "sqlmanager.h"
struct Dishes
{
    int id;
    int count;
    int state;
    double price;
    int type;
    QString name;
};

class DishesData : public QObject
{
    Q_OBJECT
public:
    explicit DishesData(QObject *parent = 0);
    
signals:
    
public slots:
    Dishes dishInfo(int dishId);
};

inline DishesData *dishesDataInstance()
{
    static DishesData data;
    return &data;
}

#endif // DISHESDATA_H
