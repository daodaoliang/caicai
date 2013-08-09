#include "dishesdata.h"
#include <QVariant>
DishesData::DishesData(QObject *parent) :
    QObject(parent)
{
}

Dishes DishesData::dishInfo(int dishId)
{
    Dishes dishes;
    QString sql = tr("select * from dishes where dishesid = %1").arg(dishId);
    QSqlQuery query = getSqlManager()->execQuery(sql);
    if(query.next())
    {
        dishes.id = dishId;
        dishes.name = query.value(1).toString();
        dishes.price = query.value(2).toDouble();
        dishes.type = query.value(5).toInt();
    }
    else
    {
        dishes.id = -1;
    }
    return dishes;
}
