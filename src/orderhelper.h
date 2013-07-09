#ifndef ORDERHELPER_H
#define ORDERHELPER_H

#include <QObject>
struct DishesInfo
{
    int id;
    int count;
};
class OrderHelper : public QObject
{
    Q_OBJECT
public:
    explicit OrderHelper(QObject *parent = 0);
    
signals:
    
public slots:
    
public:
    bool createOrder(int tableId, const QList<DishesInfo> &dishes, const QString &memberid = "");
};

inline OrderHelper *orderHelperInstance()
{
    static OrderHelper order;
    return &order;
}

#endif // ORDERHELPER_H
