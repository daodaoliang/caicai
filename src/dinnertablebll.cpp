#include "dinnertablebll.h"
#include <QDateTime>
DinnerTableBll::DinnerTableBll(QObject *parent) :
    QObject(parent)
{
}

bool DinnerTableBll::openTable(const QString &tableId, int guestNumber)
{
    QString orderId = createOrderId(tableId);
    return dinnerTableDataInstance()->openTable(tableId, orderId, guestNumber);
}

bool DinnerTableBll::closeTable(const QString &tableId)
{
    return dinnerTableDataInstance()->closeTable(tableId);
}


QString DinnerTableBll::createOrderId(const QString &tableId)
{
    return tr("%1%2").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")).arg(tableId);
}
