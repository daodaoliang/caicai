#ifndef DISHESINFOBLL_H
#define DISHESINFOBLL_H

#include <QObject>
#include "dishesdata.h"

class DishesInfoBll : public QObject
{
    Q_OBJECT
public:
    explicit DishesInfoBll(QObject *parent = 0);
    
signals:
    
public slots:
    QList<Dishes> getDishesInfo(const QString &orderId);
    bool backDish(const QString &orderId, int dishId,
                       int count, int operatorId,
                       int payType, const QString &cardId, const QString &tableId);
private:
    //ºÏ²¢¶©µ¥
    void combineDishes(QList<Dishes> &dishesInfo);
};

inline DishesInfoBll *dishesInfoBllInstance()
{
    static DishesInfoBll bll;
    return &bll;
}

#endif // DISHESINFOBLL_H
