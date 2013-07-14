#include "orderhelper.h"
#include "sqlmanager.h"
#include <QDebug>
#include <QSqlError>
OrderHelper::OrderHelper(QObject *parent) :
    QObject(parent)
{
}

bool OrderHelper::createOrder(const QString &tableId, const QList<DishesInfo> &dishes,const QString &wasteId, const QString &memberid)
{
    //��ʼ����
    QSqlDatabase *db = getSqlManager()->getdb();

    if(db->transaction())
    {
//        //��������
//        QString sql = tr("insert into diningtable (id, tablename, state, guestnumber, waiterid) values ('%1', '%1', 1, 1, '0001')").arg(tableId);
        QSqlQuery query(*db);
//        if(!query.exec(sql))
//        {
//            //�ع�
//            qDebug() << db->lastError();
//            db->rollback();
//            return false;
//        }
        //������ˮ��
        QString serialId = tr("%1%2").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss")).arg(tableId);
        //���붩��
        QString sql = tr("insert into orderinfo (orderid, orderstate, begintime, endtime, accounts, paid, tableid, memberid, wasteid) values ('%1', 0, '%2', null, 0,0, '%3', '%4', '%5')")
                .arg(serialId).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(tableId).arg(memberid).arg(wasteId);
        if(!query.exec(sql))
        {
            //�ع�
            db->rollback();
            return false;
        }
        //ѭ�����붩������
        foreach(DishesInfo info, dishes)
        {
            sql = tr("insert into orderdetail (orderid, dishesid, dishescount, dishestype, handletime) values ('%1', %2, %3, %5, '%4')")
                    .arg(serialId).arg(info.id).arg(info.count).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(info.type);
            if(!query.exec(sql))
            {
                //�ع�
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