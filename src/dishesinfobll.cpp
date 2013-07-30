#include "dishesinfobll.h"
#include "dinnertabledata.h"
#include "orderdata.h"
#include <QSqlQuery>
#include <QVariant>
DishesInfoBll::DishesInfoBll(QObject *parent) :
    QObject(parent)
{
}

QList<Dishes> DishesInfoBll::getDishesInfo(const QString &orderId)
{
    QList<Dishes> dishesList;

    if(!orderId.isEmpty())
    {
        QSqlQuery query = orderDataInstance()->getDishesInfo(orderId);
        Dishes dishesInfo;
        while(query.next())
        {
            dishesInfo.name = query.value(0).toString();
            dishesInfo.count = query.value(1).toInt();
            dishesInfo.price = query.value(2).toDouble();
            dishesInfo.state = query.value(3).toInt();
            dishesList.append(dishesInfo);
        }
    }
    return dishesList;
}
