#include "dinnertabledata.h"
#include "sqlmanager.h"
#include <QVariant>
DinnerTableData::DinnerTableData(QObject *parent) :
    QObject(parent)
{
}

bool DinnerTableData::openTable(const QString &tableId, const QString &orderId, int peopleCount)
{
    //判断是否没有撤台
    QString sql = tr("select orderid from diningtable where id = '%1'").arg(tableId);
    QSqlQuery query = getSqlManager()->execQuery(sql);
    if(query.next())
    {
        if(query.value(0).toString().isEmpty())
        {
            sql = tr("update diningtable set orderid = '%1',guestnumber = %2, state = 1 where id = '%3'")
                    .arg(orderId).arg(peopleCount).arg(tableId);
            query = getSqlManager()->execQuery(sql);
            if(query.numRowsAffected() == 1)
            {
                return true;
            }
        }
    }
    return false;
}

bool DinnerTableData::combineTable(const QStringList &tableList, const QString &orderId)
{
    return true;
}

bool DinnerTableData::closeTable(const QString &tableId)
{
    QString sql = tr("update diningtable set orderid = '', guestnumber = 0, state = 0 where id = '%1'").arg(tableId);
    QSqlQuery query = getSqlManager()->execQuery(sql);
    if(query.numRowsAffected() == 1)
    {
        return true;
    }
    return false;
}

bool DinnerTableData::changeTable(const QString &sourceTableId, const QString &destTableId)
{
    QString sql = tr("select state, orderid, guestnumber from diningtable where id = '%1'").arg(sourceTableId);
    QSqlQuery query = getSqlManager()->execQuery(sql);
    if(query.next())
    {
        int state = query.value(0).toInt();
        if(state)
        {
            QString orderId = query.value(1).toString();
            int guestNumber = query.value(2).toInt();
            int destState = getOrderState(destTableId);
            if(destState == 0)
            {
                sql = tr("update diningtable state = 1, orderid = '%1', guestnumber = %2 where id = '%3'")
                        .arg(orderId).arg(guestNumber).arg(destTableId);
                query = getSqlManager()->execQuery(sql);
                if(query.numRowsAffected() == 1)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

QString DinnerTableData::getOrderByTableId(const QString &tableId)
{
    QString sql = tr("select orderid from diningtable where id = '%1'").arg(tableId);
    QSqlQuery query = getSqlManager()->execQuery(sql);
    if(query.next())
    {
        return query.value(0).toString();
    }
    return "";
}

int DinnerTableData::getOrderState(const QString &tableId)
{
    QString sql = tr("select state from diningtable where id = '%1'").arg(tableId);
    QSqlQuery query = getSqlManager()->execQuery(sql);
    if(query.next())
    {
        return query.value(0).toInt();
    }
    return -1;
}
