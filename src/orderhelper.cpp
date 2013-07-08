#include "orderhelper.h"
#include "sqlmanager.h"
#include <QDebug>
#include <QSqlError>
OrderHelper::OrderHelper(QObject *parent) :
    QObject(parent)
{
}

bool OrderHelper::createOrder(int tableId, const QList<DishesInfo> &dishes, const QString &memberid)
{
    //开始事务
    QSqlDatabase *db = getSqlManager()->getdb();

    if(db->transaction())
    {
        //插入桌号
        QString sql = tr("insert into diningtable (id, tablename, state, guestnumber, waiterid) values ('%1', '%1', 1, 1, '0001')").arg(tableId);
        QSqlQuery query(*db);
        if(!query.exec(sql))
        {
            //回滚
            qDebug() << db->lastError();
            db->rollback();
            return false;
        }
        //生成流水号
        QString serialId = tr("%1%2").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")).arg(tableId);
        //插入订单
        sql = tr("insert into orderinfo (orderid, orderstate, begintime, endtime, accounts, paid, tableid, memberid) values ('%1', 0, '%2', null, 0,0, '%3', '%4')")
                .arg(serialId).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(tableId).arg(memberid);
        if(!query.exec(sql))
        {
            //回滚
            db->rollback();
            return false;
        }
        //循环插入订单详情
        foreach(DishesInfo info, dishes)
        {
            sql = tr("insert into orderdetail (orderid, dishesid, dishescount, dishestype, handletime) values ('%1', %2, %3, 0, '%4')")
                    .arg(serialId).arg(info.id).arg(info.count).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            if(!query.exec(sql))
            {
                //回滚
                db->rollback();
                return false;
            }
        }
        if(!db->commit())
        {
            db->rollback();
            return false;
        }
        return true;
    }
}
