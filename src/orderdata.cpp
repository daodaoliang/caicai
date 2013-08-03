#include "orderdata.h"

OrderData::OrderData(QObject *parent) :
    QObject(parent)
{
}

QSqlQuery OrderData::getDishesInfo(const QString &orderId)
{
    QString sql = tr("select dishes.dishesname, orderdetail.dishescount, dishes.price, orderdetail.dishestype, dishes.dishesid from orderdetail " \
                     "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid where orderid = '%1'").arg(orderId);
    return getSqlManager()->execQuery(sql);
}

QSqlQuery OrderData::backDish(const QString &orderId, int dishId,
                              int count, int operatorId,
                              int payType, const QString &cardId)
{
    QString sql = tr("insert into orderdetail (orderid, dishesid, dishescount, dishestype, handletime, paytype, cardid, operatorId)"\
                     " values ('%1', %2, %3, %4, '%5', %6, '%7', '%8')")
            .arg(orderId).arg(dishId).arg(count).arg(1).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(payType).arg(cardId).arg(operatorId);
    return getSqlManager()->execQuery(sql);
}
