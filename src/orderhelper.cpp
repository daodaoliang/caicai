#include "orderhelper.h"
#include "sqlmanager.h"
#include <QDebug>
#include <QSqlError>
OrderHelper::OrderHelper(QObject *parent) :
    QObject(parent)
{
}

bool OrderHelper::createOrder(const QString &tableId, QList<DishesInfo> &dishes,const QString &wasteId, int userid, double &totalPrice, QString &orderId, const QString &memberid)
{
    //开始事务
    QSqlDatabase *db = getSqlManager()->getdb();

    if(db->transaction())
    {
        //        //插入桌号
        //        QString sql = tr("insert into diningtable (id, tablename, state, guestnumber, waiterid) values ('%1', '%1', 1, 1, '0001')").arg(tableId);
        QSqlQuery query(*db);
        //        if(!query.exec(sql))
        //        {
        //            //回滚
        //            qDebug() << db->lastError();
        //            db->rollback();
        //            return false;
        //        }
        //获取总价
        //QString sql = tr("select price, dishesname, typeid from dishes where dishesid in(%1").arg(dishes.first().id);
        //QString sql = tr("select price, dishesname, typeid from dishes where dishesid in(%1) ORDER BY FIND_IN_SET(dishesid '%1')").arg(dishes.first().id);
        QString id = "";
        QString sql = "";
        if(dishes.count() > 0)
        {
            id = tr("%1").arg(dishes[0].id);
            for(int i = 1; i < dishes.count(); i++)
            {
                id.append(tr(",%1").arg(dishes[i].id));
            }
        }
        else
        {
            return false;
        }
        sql = tr("select price, dishesname, typeid from dishes where dishesid in(%1) ORDER BY FIND_IN_SET(dishesid, '%1')").arg(id);
        //sql.append(")");
        qDebug() << sql;
        QSqlQuery *priceQuery = getSqlManager()->ExecQuery(sql);
        double paid = 0;
        int index = 0;
        while(priceQuery->next())
        {
            paid += priceQuery->value(0).toDouble() * dishes[index].count;
            qDebug()<<priceQuery->value(0).toDouble()<<dishes[index].count<<QString::number(paid);
            dishes[index].name = priceQuery->value(1).toString();
            dishes[index].dishType = priceQuery->value(2).toInt();
            qDebug()<<"sql-----"<<dishes[index].name<<dishes[index].count;
            index++;
        }
        if(dishes.first().type == 1)
        {
            paid *= -1;
        }
        //进行打折
        double discountMoney = discount(dishes);
        totalPrice = paid - discountMoney;
        //生成流水号
        QString serialId = tr("%1%2").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")).arg(tableId);
        orderId = serialId;
        //插入订单
        sql = tr("insert into orderinfo (orderid, orderstate, begintime, endtime, accounts, paid, tableid, memberid, wasteid, userid) values ('%1', 0, '%2', null, %7,%8, '%3', '%4', '%5', %6)")
                .arg(serialId).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(tableId).arg(memberid).arg(wasteId).arg(userid).arg(paid).arg(paid - discountMoney);
        if(!query.exec(sql))
        {
            //回滚
            db->rollback();
            return false;
        }
        //循环插入订单详情
        foreach(DishesInfo info, dishes)
        {
            sql = tr("insert into orderdetail (orderid, dishesid, dishescount, dishestype, handletime) values ('%1', %2, %3, %5, '%4')")
                    .arg(serialId).arg(info.id).arg(info.count).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(info.type);
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
    return false;
}

double OrderHelper::discount(QList<DishesInfo> &dishes)
{
    if(dishes.count() == 0)
    {
        return 0;
    }
    int a = 0;
    int b = 0;
    int c = 0;

    for(int i = 0; i < dishes.count(); i++)
    {
        if(dishes[i].dishType == 1)
        {
            a++;
        }
        if(dishes[i].dishType == 2)
        {
            b++;
        }
        if(dishes[i].dishType == 3)
        {
            c++;
        }

    }
    int count = qMin(a, b);
    count = qMin(count, c);
    //套餐中的饮料加套餐备注
    int d = 0;
    for(int i = 0; i < dishes.count(); i++)
    {
        if(dishes[i].dishType == 1)
        {
            QString name = dishes[i].name;
            dishes[i].name = name+"(套餐)";
            d++;
        }
        if(d == count)
        {
            break;
        }
    }
    return count * 6 * (dishes.first().type ? -1 : 1);
}
