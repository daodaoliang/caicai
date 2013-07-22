#ifndef BACKPRINTER_H
#define BACKPRINTER_H

#include <QObject>
#include <QTcpSocket>
#include "orderhelper.h"
class BackPrinter : public QObject
{
    Q_OBJECT
public:
    explicit BackPrinter(QObject *parent = 0);
    
signals:
    
public slots:
    bool print(const QString &tableId, const QList<DishesInfo> &dishes, const QString &orderId, double paid);
    bool printDishes(const QString &tableId, const QList<DishesInfo> &dishes, const QString &orderId, double paid);
    QByteArray createLine(const QString &text);
    QByteArray createDishes(const DishesInfo &dishes);
    QByteArray createSplit();
private:
    QTcpSocket m_socket;
};

inline BackPrinter *getBackPrinter()
{
    static BackPrinter w;
    return &w;
}

#endif // BACKPRINTER_H
