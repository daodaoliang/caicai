#include "icommandhandler.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QStringList>
#include <QApplication>
#include <QFile>
#include "sqlmanager.h"
#include <windows.h>
#include <QSqlResult>
#include "dinnerwidget.h"
#include "orderhelper.h"
#include "backprinter.h"
ICommandHandler::ICommandHandler() :
    QObject()
{
}

void ICommandHandler::reply(const QStringList &replyList, int index)
{
    if(replyList.count() > 0)
    {
        QString fileName = tr("%1/TXT/R%2.txt").arg(qApp->applicationDirPath()).arg(index);
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            for(int i = 0; i < replyList.count(); i++)
            {
                file.write(replyList[i].toLocal8Bit().data());
                file.write("\n");
            }
        }
    }
}


void LoginHandler::handleCommand(const QStringList &cmdDetail, int index)
{
    QStringList replyList;
    replyList.append(cmdDetail[0].trimmed());
    if(cmdDetail.size() >= 2)
    {
        QString user = cmdDetail[1].mid(10, 4).trimmed();
        QString password = cmdDetail[1].mid(15, 10).trimmed();
        int userId = 0;
        QString nickName = getSqlManager()->login(user, password, cmdDetail[0].right(3), userId);
        if(nickName.isEmpty())
        {
            replyList.append("0 登录失败");
            reply(replyList, index);
            return;
        }
        else
        {
            replyList.append("1 登录成功");
            reply(replyList, index);
            return;
        }
    }
    replyList.append("0 验证失败");
    reply(replyList, index);
}


void OpenMachineHandler::handleCommand(const QStringList &cmdDetail, int index)
{

}


void OpenTableHandler::handleCommand(const QStringList &cmdDetail, int index)
{
    QStringList replyList;
    replyList.append(cmdDetail[0].trimmed());
    if(cmdDetail.size() >= 2)
    {
        //餐桌编号
        QString tableId = cmdDetail[1].left(4);
        tableId = tr("%1").arg(tableId.toInt(), 4, 10, QLatin1Char('0'));
        //人数
        int guestNumber = cmdDetail[1].mid(5, 2).toInt();
        QString waiterId = cmdDetail[1].right(5);
        QString sql = tr("update diningtable set state = 1, guestnumber = %1, waiterid = %2, lastopentime = '%3' where id = '%4'")
                .arg(guestNumber).arg(waiterId).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(tableId);
        QSqlQuery *query = getSqlManager()->ExecQuery(sql);
        if(query != NULL)
        {
            if(query->numRowsAffected() == 1)
            {
                //TODO:处理数据库添加订单
                replyList.append(tableId + "开台成功！");
                reply(replyList, index);
                //界面显示
                dinnerWidget()->updateData();
                return;
            }

        }

        replyList.append(tableId + "开台失败");
        reply(replyList, index);
    }
    return;
}


void ChangeTableHandler::handleCommand(const QStringList &cmdDetail, int index)
{
    qDebug() << cmdDetail;


}


void OrderHandler::handleCommand(const QStringList &cmdDetail, int index)
{
    qDebug() << cmdDetail;
    QStringList replyList;
    replyList.append(cmdDetail[0].trimmed());
    if(cmdDetail.count() >= 3)
    {
        //确认已经开台
        QString tableId = cmdDetail[1].left(7);
        tableId = tr("%1").arg(tableId.toInt(), 4, 10, QLatin1Char('0'));
        QString sql = tr("select * from diningtable where id = '%1' and state = 1").arg(tableId);
        QSqlQuery *query = getSqlManager()->ExecQuery(sql);
        if(query != NULL)
        {
            if(query->next())
            {
                //确认流水号
                QString machineId = cmdDetail[0].right(3);
                QString wasteId = machineId + QDate::currentDate().toString("yyyyMMdd") + cmdDetail[1].right(8);
                sql = tr("select * from orderinfo where wasteid = '%1'").arg(wasteId);
                query = getSqlManager()->ExecQuery(sql);
                if(query != NULL)
                {
                    if(!query->next())
                    {
                        //获取操作员编号
                        sql = tr("select userid from login where machineid = '%1'").arg(cmdDetail[0].right(3));
                        query = getSqlManager()->ExecQuery(sql);
                        if(query != NULL)
                        {
                            if(query->next())
                            {
                                int userid = query->value(0).toInt();
                                QList<DishesInfo> dishesList;
                                DishesInfo info;

                                //添加菜品
                                for(int i = 2; i < cmdDetail.count(); i++)
                                {
                                    info.id = cmdDetail[i].mid(8, 5).toInt();
                                    info.count = cmdDetail[i].mid(14, 4).toInt();
                                    info.type = 0;
                                    dishesList.append(info);
                                }
                                QString orderId;
                                double money = 0;
                                bool result = orderHelperInstance()->createOrder(tableId,dishesList, wasteId, userid ,money, orderId);
                                if(result)
                                {
                                    //减少库存
                                    //进行打印
                                    getBackPrinter()->print(tableId, dishesList, orderId, money);
                                    //回复正常
                                    replyList.append("点菜成功");
                                    reply(replyList, index);
                                    return;
                                }
                                else
                                {
                                    replyList.append("点菜失败");
                                    reply(replyList, index);
                                    return;
                                }
                            }
                        }


                    }
                    else
                    {
                        replyList.append("此菜单已点");
                        reply(replyList, index);
                        return;
                    }
                }
            }
        }
        else
        {
            replyList.append("此台未开");
            replyList.append("请先开台");
            reply(replyList, index);
            return;
        }
    }
    else
    {
        replyList.append("格式错误");
        reply(replyList, index);
        return;
    }
}


void MessageHandler::handleCommand(const QStringList &cmdDetail, int index)
{
    qDebug() << cmdDetail;

}


void BackDishHandler::handleCommand(const QStringList &cmdDetail, int index)
{
//    qDebug() << cmdDetail;
//    QStringList replyList;
//    replyList.append(cmdDetail[0].trimmed());
//    if(cmdDetail.count() == 2)
//    {
//        //确认已经开台
//        QString tableId = cmdDetail[1].left(7);
//        tableId = tr("%1").arg(tableId.toInt(), 4, 10, QLatin1Char('0'));
//        QString sql = tr("select * from diningtable where id = '%1' and state = 1").arg(tableId);
//        QSqlQuery *query = getSqlManager()->ExecQuery(sql);
//        if(query != NULL)
//        {
//            if(query->next())
//            {
//                //获取操作员编号
//                sql = tr("select userid from login where machineid = '%1'").arg(cmdDetail[0].right(3));
//                query = getSqlManager()->ExecQuery(sql);
//                if(query != NULL)
//                {
//                    if(query->next())
//                    {
//                        int userid = query->value(0).toInt();
//                        QList<DishesInfo> dishesList;
//                        DishesInfo info;
//                        info.id = cmdDetail[1].mid(8, 5).toInt();
//                        info.count = cmdDetail[1].mid(19, 4).toInt();
//                        info.type = 1;
//                        dishesList.append(info);
//                        bool result = orderHelperInstance()->createOrder(tableId,dishesList, "", userid);
//                        if(result)
//                        {
//                            //减少库存
//                            //进行打印
//                            //回复正常
//                            replyList.append("退菜成功");
//                            reply(replyList, index);
//                            return;
//                        }
//                        else
//                        {
//                            replyList.append("退菜失败");
//                            reply(replyList, index);
//                            return;
//                        }
//                    }
//                }
//            }
//            else
//            {
//                replyList.append("此台未开");
//                reply(replyList, index);
//                return;
//            }
//        }
//        else
//        {
//            replyList.append("查询失败");
//            reply(replyList, index);
//            return;
//        }
//    }
//    else
//    {
//        replyList.append("格式错误");
//        reply(replyList, index);
//        return;
//    }

}
