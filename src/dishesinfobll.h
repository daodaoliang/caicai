#ifndef DISHESINFOBLL_H
#define DISHESINFOBLL_H

#include <QObject>
struct Dishes
{
    int id;
    int count;
    int state;
    double price;
    int type;
    QString name;
};
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
                       int payType, const QString &cardId);
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
