#ifndef DINNERTABLEBLL_H
#define DINNERTABLEBLL_H

#include <QObject>
#include "dinnertabledata.h"
class DinnerTableBll : public QObject
{
    Q_OBJECT
public:
    explicit DinnerTableBll(QObject *parent = 0);
    
signals:
    
public slots:
    bool openTable(const QString &tableId, int guestNumber);
    bool closeTable(const QString &tableId);
    bool combineTable(const QString &tableId1, const QString &tableId2);
    bool splitTable(const QString &tableId);

private:
    QString createOrderId(const QString &tableId);
};

inline DinnerTableBll *dinnerTableBllInstance()
{
    static DinnerTableBll bll;
    return &bll;
}

#endif // DINNERTABLEBLL_H
