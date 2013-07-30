#include "orderhelper.h"
#include "sqlmanager.h"
#include <QDebug>
#include <QSqlError>
#include "vipwidget.h"
OrderHelper::OrderHelper(QObject *parent) :
    QObject(parent)
{
    m_disOrangre.clear();
    m_disOrangre.enqueue("葡萄汁");
    m_disOrangre.enqueue("冰糖雪梨汁");
    m_disOrangre.enqueue("樱桃汁");
    m_disOrangre.enqueue("菠萝汁");
    m_disOrangre.enqueue("红枣养颜豆浆");
    m_disOrangre.enqueue("酸梅汁");
    m_disOrangre.enqueue("雀巢芒果C");
}

bool OrderHelper::createOrder(const QString &tableId, QList<DishesInfo> &dishes,const QString &wasteId, int userid, double &totalPrice, QString &orderId, const QString &memberid,  int payType)
{
    //开始事务
    QSqlDatabase *db = getSqlManager()->getdb();

    //套餐判断
    if(!judgePackages(dishes))
    {
        return false;
    }

    if(db->transaction())
    {
        QSqlQuery query(*db);
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
        qDebug()<<"order"<<paid<<totalPrice;
        //如果使用卡片则在此处扣钱
        QString cardId = "";
        if(payType != 0)
        {
            cardId = vipWidget()->payMoney(totalPrice);
            if(cardId == "")
            {
                db->rollback();
                return false;
            }
        }
        //判断是插入还是更新
        if(!query.exec(tr("select * from orderinfo where orderid = '%1'").arg(orderId) ))
        {
            db->rollback();
            return false;
        }
        if(query.next())
        {
            double lastAccounts = query.value(4).toDouble();
            double lastPaid = query.value(5).toDouble();
            //更新操作
            sql = tr("update orderinfo set accounts = %1, paid = %2 where orderid = '%3'").arg(paid + lastAccounts).arg(lastPaid + paid - discountMoney).arg(orderId);
            if(!query.exec(sql))
            {
                //回滚
                db->rollback();
                return false;
            }
        }
        else
        {
            //插入订单
            sql = tr("insert into orderinfo (orderid, orderstate, begintime, endtime, accounts, paid, tableid, memberid, wasteid, userid) values ('%1', 0, '%2', null, %7,%8, '%3', '%4', '%5', %6)")
                    .arg(orderId).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(tableId).arg(memberid).arg(wasteId).arg(userid).arg(paid).arg(paid - discountMoney);
            if(!query.exec(sql))
            {
                //回滚
                db->rollback();
                return false;
            }
        }

        //循环插入订单详情
        foreach(DishesInfo info, dishes)
        {
            sql = tr("insert into orderdetail (orderid, dishesid, dishescount, dishestype, handletime, paytype, cardid) values ('%1', %2, %3, %5, '%4', '%6', '%7')")
                    .arg(orderId).arg(info.id).arg(info.count).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(info.type).arg(payType).arg(cardId);
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
        qDebug()<<"name"<<dishes[i].name;
        if(dishes[i].dishType == 1 && m_disOrangre.contains(dishes[i].name))
        {
            qDebug()<<"name"<<dishes[i].name;
            a= a+dishes[i].count;
        }
        if(dishes[i].dishType == 2)
        {
            //b++;
            b= b+dishes[i].count;
        }
        if(dishes[i].dishType == 3)
        {
            //c++;
            c=c+dishes[i].count;
        }

    }
    int count = qMin(a, b);
    count = qMin(count, c);
    qDebug()<<"discout"<<a<<b<<c<<count;
    //套餐中的饮料加套餐备注
    //    if(count > 0)
    //    {
    //        int d = 0;
    //        for(int i = 0; i < dishes.count(); i++)
    //        {
    //            if(dishes[i].dishType == 1 && m_disOrangre.contains(dishes[i].name))
    //            {
    //                QString name = dishes[i].name;
    //                dishes[i].name = name+"(套餐)";
    //                d++;
    //            }
    //            if(d == count)
    //            {
    //                break;
    //            }
    //        }
    //    }
    //return count * 6 * (dishes.first().type ? -1 : 1);
    return 0;
}

bool OrderHelper::isDiscount(const QString &name)
{
    return m_disOrangre.contains(name);
}

bool OrderHelper::judgePackages(QList<DishesInfo> &dishes)
{
    //套餐菜数量
    int packagesCount = 0;
    for(int i = 0; i < dishes.count(); i++)
    {
        if(dishes.at(i).name.contains("套餐"))
        {
            packagesCount += dishes.at(i).count;
        }
    }
    //米线数量
    int mixianCount = getCountByType(dishes, 3);
    //小菜数量
    int xiaoCaiCount = getCountByType(dishes, 2);
    //允许套餐数量
    int allowCount = qMin(mixianCount, xiaoCaiCount);

    return allowCount >= packagesCount;
}

int OrderHelper::getCountByType(QList<DishesInfo> &dishes, int type)
{
    int count = 0;
    for(int i = 0; i < dishes.count(); i++)
    {
        if(dishes.at(i).dishType == type)
        {
            count += dishes.at(i).count;
        }
    }
    return count;

}
