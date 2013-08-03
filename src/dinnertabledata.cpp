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
    QString sql = tr("select state from diningtable where id = '%1'").arg(tableId);
    QSqlQuery query = getSqlManager()->execQuery(sql);
    if(query.next())
    {
        if(query.value(0).toInt() == 0)
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

bool DinnerTableData::combineTable(const QString &sourceTableId, const QString &destTableId)
{
    QSqlDatabase *db = getSqlManager()->getdb();
    if(!db->transaction())
    {
        return false;
    }
    QSqlQuery query(*db);
    //删除一个桌子
    QString sql = tr("delete from diningtable where id = '%1'").arg(destTableId);
    if(!query.exec(sql))
    {
        db->rollback();
        return false;
    }
    //更新一个桌子
    sql = tr("update diningtable set type = 1, tablename = concat(tablename,'(并)'), relateid = '%1' where id = '%2'").arg(destTableId).arg(sourceTableId);
    if(!query.exec(sql))
    {
        db->rollback();
        return false;
    }
    if(!db->commit())
    {
        db->rollback();
        return false;
    }
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

bool DinnerTableData::splitTable(const QString &tableId)
{
    QString name = QString::number(tableId.toInt()) + "号桌";
    QString sql = tr("INSERT into diningtable (diningtable.id, diningtable.tablename, diningtable.type, diningtable.state)"\
                     "VALUES ('%1', '%2', 2, 0)").arg(tableId).arg(name + "(拆)");
    QSqlQuery query = getSqlManager()->execQuery(sql);
    if(query.numRowsAffected() == 1)
    {
        return true;
    }
    else
    {
        return false;
    }

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

QString DinnerTableData::getNewId()
{
    QString tableId;
    QSqlQuery query = getSqlManager()->execQuery("select max(id) from diningtable");
    if(query.next())
    {
        QString maxId = query.value(0).toString();
        tableId = tr("%1").arg(maxId.toInt() + 1, 4, 10, QLatin1Char('0'));
    }
    return tableId;
}

int DinnerTableData::tableType(const QString &tableId)
{
    QString sql = tr("select type from diningtable where id = '%1'").arg(tableId);
    QSqlQuery query = getSqlManager()->execQuery(sql);
    if(query.next())
    {
        return query.value(0).toInt();
    }
    return -1;
}

bool DinnerTableData::deleteTable(const QString &tableId)
{
    QString sql = tr("delete from diningtable where id = '%1'").arg(tableId);
    QSqlQuery query = getSqlManager()->execQuery(sql);
    return query.numRowsAffected() == 1;
}

bool DinnerTableData::restoreTable(const QString &tableId)
{
    QSqlDatabase *db = getSqlManager()->getdb();
    if(!db->transaction())
    {
        return false;
    }
    QSqlQuery query(*db);
    if(!query.exec(tr("select relateid from diningtable where id = '%1'").arg(tableId)))
    {
        db->rollback();
        return false;
    }
    if(!query.next())
    {
        db->rollback();
        return false;
    }
    QString relateId = query.value(0).toString();
    QString name = QString::number(relateId.toInt()) + "号桌";
    //增加一个桌子
    QString sql = tr("INSERT into diningtable (diningtable.id, diningtable.tablename, diningtable.type, diningtable.state)"\
                     "VALUES ('%1', '%2', 0, 0)").arg(relateId).arg(name);
    if(!query.exec(sql))
    {
        db->rollback();
        return false;
    }
    //更新一个桌子
    name = QString::number(tableId.toInt()) + "号桌";

    sql = tr("update diningtable set type = 0, tablename = '%1', relateid = '', state = 0, guestnumber = 0 where id = '%2'")
            .arg(name).arg(tableId);
    if(!query.exec(sql))
    {
        db->rollback();
        return false;
    }
    if(!db->commit())
    {
        db->rollback();
        return false;
    }
    return true;
}


