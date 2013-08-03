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
    int type = dinnerTableDataInstance()->tableType(tableId);
    switch (type) {
    case 0:
        return dinnerTableDataInstance()->closeTable(tableId);
    case 1:
        return dinnerTableDataInstance()->restoreTable(tableId);
    case 2:
        return dinnerTableDataInstance()->deleteTable(tableId);
    default:
        break;
    }
    return false;
}

bool DinnerTableBll::combineTable(const QString &tableId1, const QString &tableId2)
{
    int type = dinnerTableDataInstance()->tableType(tableId1);
    int type1 = dinnerTableDataInstance()->tableType(tableId2);
    if(type != 0 || type1 != 0)
    {
        return false;
    }
    return dinnerTableDataInstance()->combineTable(tableId1, tableId2);
}

bool DinnerTableBll::splitTable(const QString &tableId)
{
    //判断是否是正常桌子
    if(!dinnerTableDataInstance()->tableType(tableId) == 0)
    {
        return false;
    }
    QString newId = dinnerTableDataInstance()->getNewId();

    return dinnerTableDataInstance()->splitTable(newId);
}


QString DinnerTableBll::createOrderId(const QString &tableId)
{
    return tr("%1%2").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")).arg(tableId);
}
