#ifndef ORDERHELPER_H
#define ORDERHELPER_H

#include <QObject>
struct DishesInfo
{
    int id;
    int count;
    int type;
    double price;
};
class OrderHelper : public QObject
{
    Q_OBJECT
public:
    explicit OrderHelper(QObject *parent = 0);
    
signals:
    
public slots:
    
public:
    bool createOrder(const QString &tableId, const QList<DishesInfo> &dishes,const QString &wasteId,  int userid, const QString &memberid = "");
};

inline OrderHelper *orderHelperInstance()
{
    static OrderHelper order;
    return &order;
}

#endif // ORDERHELPER_H
