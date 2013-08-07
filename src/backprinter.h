#ifndef BACKPRINTER_H
#define BACKPRINTER_H

#include <QObject>
#include <QTcpSocket>
#include "orderhelper.h"
#include "configerfileprocesser.h"

class BackPrinter : public QObject
{
    Q_OBJECT
public:
    explicit BackPrinter(const QString &ip, QObject *parent = 0);
    
signals:
    
public slots:
    bool print(const QString &tableId, const QList<DishesInfo> &dishes, const QString &orderId, double paid);
    bool printDishes(const QString &tableId, const QList<DishesInfo> &dishes,
                     const QString &orderId, double paid, const QString &ip);
    QByteArray createLine(const QString &text);
    QByteArray createDishes(const DishesInfo &dishes);
    QByteArray createSplit();
private:
    QString m_ip;
};

inline BackPrinter *getBackPrinter()
{
    static BackPrinter w(getConfigerFileInstance()->printerIp());
    return &w;
}


#endif // BACKPRINTER_H
