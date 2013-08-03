#include "dishesinfobll.h"
#include "dinnertabledata.h"
#include "orderdata.h"
#include <QSqlQuery>
#include <QVariant>
#include "dishesdata.h"
#include "backprinter.h"
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
            dishesInfo.id = query.value(4).toInt();
            dishesList.append(dishesInfo);
        }
    }
    combineDishes(dishesList);
    return dishesList;
}

bool DishesInfoBll::backDish(const QString &orderId, int dishId, int count, int operatorId, int payType, const QString &cardId,
                             const QString &tableId)
{
    QSqlQuery query = orderDataInstance()->backDish(orderId, dishId, count, operatorId, payType, cardId);
    if(query.numRowsAffected() == 1)
    {
        //打印
        Dishes dishes = dishesDataInstance()->dishInfo(dishId);
        dishes.count = count;
        QList<DishesInfo> dishesList;
        DishesInfo dishesInfo;
        dishesInfo.count = dishes.count;
        dishesInfo.id = dishes.id;
        dishesInfo.name = dishes.name;
        dishesInfo.price = dishes.price;
        dishesList.append(dishesInfo);
        getBackPrinter()->print(tableId, dishesList, orderId, 0);
        return true;
    }
    else
    {
        return false;
    }
}

void DishesInfoBll::combineDishes(QList<Dishes> &dishesInfo)
{
    QMap<int, Dishes> dishesMap;
    Dishes newDishes;
    for(int i = 0; i < dishesInfo.count(); i++)
    {
        //数据已经存在
        if(dishesMap.find(dishesInfo.at(i).id) != dishesMap.end())
        {
            int multiplier = dishesInfo.at(i).state == 1 ? -1 : 1;
            newDishes = dishesMap.value(dishesInfo.at(i).id);
            newDishes.count += multiplier * dishesInfo.at(i).count;
            dishesMap[dishesInfo.at(i).id] = newDishes;
        }
        //数据不存在
        else
        {
            dishesMap[dishesInfo.at(i).id] = dishesInfo.at(i);
        }
    }
    dishesInfo.clear();
    dishesInfo = dishesMap.values();
}

