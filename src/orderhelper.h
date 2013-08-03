#ifndef ORDERHELPER_H
#define ORDERHELPER_H

#include <QObject>
#include <QQueue>
struct DishesInfo
{
    int id;
    int count;
    int type;
    double price;
    int dishType;
    QString name;
};
class OrderHelper : public QObject
{
    Q_OBJECT
public:
    explicit OrderHelper(QObject *parent = 0);
    
signals:
    
public slots:
    
public:
    bool createOrder(const QString &tableId, QList<DishesInfo> &dishes,const QString &wasteId,  int userid, double &totalPrice,const QString &orderId,const QString &memberid = "", int payType = 0);
    double discount(QList<DishesInfo> &dishes);
    bool isDiscount(const QString &name);
private:
    bool judgePackages(QList<DishesInfo> &dishes);
    int getCountByType(QList<DishesInfo> &dishes, int type);
private:
    QQueue<QString> m_disOrangre;
};

inline OrderHelper *orderHelperInstance()
{
    static OrderHelper order;
    return &order;
}
#endif // ORDERHELPER_H
