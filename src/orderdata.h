#ifndef ORDERDATA_H
#define ORDERDATA_H

#include <QObject>
#include "sqlmanager.h"
class OrderData : public QObject
{
    Q_OBJECT
public:
    explicit OrderData(QObject *parent = 0);
    
signals:
    
public slots:
    QSqlQuery getDishesInfo(const QString &orderId);
};

inline OrderData *orderDataInstance()
{
    static OrderData data;
    return &data;
}

#endif // ORDERDATA_H
