#include "orderdata.h"

OrderData::OrderData(QObject *parent) :
    QObject(parent)
{
}

QSqlQuery OrderData::getDishesInfo(const QString &orderId)
{
    QString sql = tr("select dishes.dishesname, orderdetail.dishescount, dishes.price, orderdetail.dishestype from orderdetail " \
                     "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid where orderid = '%1'").arg(orderId);
    return getSqlManager()->execQuery(sql);
}
