#include "icommandhandler.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QStringList>
#include <QApplication>
#include <QFile>
#include "sqlmanager.h"
#include <windows.h>
#include <QSqlResult>
#include <QMessageBox>
#include "dinnerwidget.h"
#include "orderhelper.h"
#include "backprinter.h"
#include "frontprinter.h"
#include "dinnertablebll.h"
#include "tablewidget.h"
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
        if(password.length() == 0)
        {
            if(user.length() == 0)
            {
                replyList.append("0 ע��ʧ��");
                reply(replyList, index);
                emit updateInfo();
                return;
            }else
            {
                QString sql = tr("select username from userinfo where machineid = '%1'").arg(cmdDetail[0].right(3));
                QSqlQuery *query = getSqlManager()->ExecQuery(sql);
                if(query != NULL)
                {
                    if(query->next())
                    {
                        qDebug()<<"get uset "<<query->value(0).toString()<<user;
                        if(query->value(0).toString() == user)
                        {
                            getSqlManager()->logOut(cmdDetail[0].right(3));
                            replyList.append("1 ע���ɹ�");
                            reply(replyList, index);
                            emit updateInfo();
                            return;
                        }
                    }
                }
                qDebug()<<"select no";
                replyList.append("0 ע��ʧ��");
                reply(replyList, index);
                emit updateInfo();
                return;
            }
        }
        qDebug()<<"dian cai bao"<<user<<password;
        int userId = 0;
        QString nickName = getSqlManager()->login(user, password, cmdDetail[0].right(3), userId);
        if(nickName.isEmpty())
        {
            replyList.append("0 ��¼ʧ��,��ע���ٵ�¼ ");
            reply(replyList, index);
            emit updateInfo();
            return;
        }
        else
        {
            QString sql = tr("replace into login (machineid,userid) values ('%1','%2')").arg(cmdDetail[0].right(3)).arg(userId);
            QSqlQuery *query = getSqlManager()->ExecQuery(sql);
            if(query != NULL)
            {
                replyList.append("1 ��¼�ɹ�");
                reply(replyList, index);
                emit updateInfo();
                return;
            }
            replyList.append("0 ��¼ʧ��,��ע���ٵ�¼ ");
            reply(replyList, index);
            emit updateInfo();
            return;
        }
    }
    replyList.append("0 ��֤ʧ��");
    reply(replyList, index);
    emit updateInfo();
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
        //�������
        QString tableId = cmdDetail[1].left(4);
        tableId = tr("%1").arg(tableId.toInt(), 4, 10, QLatin1Char('0'));
        //����
        int guestNumber = cmdDetail[1].mid(5, 2).toInt();
        QString waiterId = cmdDetail[1].right(5);
        bool result = dinnerTableBllInstance()->openTable(tableId, guestNumber);
        if(result)
        {
            //TODO:�������ݿ���Ӷ���
            replyList.append(tableId + "��̨�ɹ���");
            reply(replyList, index);
            //������ʾ
            dinnerWidget()->updateData();
            tableWidget()->updateView();
            return;
        }

        replyList.append(tableId + "��̨ʧ��");
        reply(replyList, index);
    }
    return;
}


void ChangeTableHandler::handleCommand(const QStringList &cmdDetail, int index)
{
    qDebug() << cmdDetail<<cmdDetail.count();
    QStringList replyList;
    replyList.append(cmdDetail[0].trimmed());
    if(cmdDetail.count() == 2)
    {
        QString oldTable = tr("%1").arg(cmdDetail[1].left(7).remove(" ").toInt(),4,10,QLatin1Char('0'));
        QString newTable = tr("%1").arg(cmdDetail[1].right(7).remove(" ").toInt(),4,10,QLatin1Char('0'));
        qDebug()<<oldTable<<newTable;
        if(oldTable == newTable)
        {
            replyList.append("��̨ʧ��");
            reply(replyList, index);
            return;
        }
        QString sql = tr("select state from diningtable where id = '%1'").arg(oldTable);
        QSqlQuery *query = getSqlManager()->ExecQuery(sql);
        if(query != NULL)
        {
            if(query->next())
            {
                if(query->value(0).toInt() == 0)
                {
                    //ԭ̨��δ��̨
                    replyList.append("ԭ̨��δ��̨");
                    reply(replyList, index);
                    return;
                }
                sql = tr("select state from diningtable where id = '%1'").arg(newTable);
                query = getSqlManager()->ExecQuery(sql);
                if(query != NULL)
                {
                    if(query->next())
                    {
                        //                        if(query->value(0).toInt() == 1)
                        //                        {
                        //                            //��̨���ѿ�̨
                        //                            replyList.append("��̨�ѿ�̨,�����»�̨");
                        //                            reply(replyList, index);
                        //                            return;
                        //                        }
                        sql = tr("update diningtable set state = 0 where id = '%1';update diningtable set state = 1 where id = '%2'").arg(oldTable).arg(newTable);
                        query = getSqlManager()->ExecQuery(sql);
                        if(query != NULL)
                        {
                            dinnerWidget()->updateData();
                            tableWidget()->updateView();
                            replyList.append("��̨�ɹ�");
                            reply(replyList, index);
                            return;
                        }
                        else
                        {
                            qDebug()<<"-----------------------------------------------------";
                            replyList.append("��̨ʧ��");
                            reply(replyList, index);
                            return;
                        }
                    }else
                    {
                        //��̨�Ų�����
                        replyList.append("��̨�Ų�����");
                        reply(replyList, index);
                        return;
                    }
                }
            }else
            {
                //�����ڸ�ԭ̨��
                replyList.append("ԭ̨�Ų�����");
                reply(replyList, index);
                return;
            }
        }
    }

}


void OrderHandler::handleCommand(const QStringList &cmdDetail, int index)
{
    qDebug() << cmdDetail;
    QStringList replyList;
    replyList.append(cmdDetail[0].trimmed());
    if(cmdDetail.count() >= 3)
    {
        //ȷ���Ѿ���̨
        QString tableId = cmdDetail[1].left(7);
        tableId = tr("%1").arg(tableId.toInt(), 4, 10, QLatin1Char('0'));
        QString sql = tr("select * from diningtable where id = '%1' and state = 1").arg(tableId);
        QSqlQuery *query = getSqlManager()->ExecQuery(sql);
        if(query != NULL)
        {
            if(query->next())
            {
                //ȷ����ˮ��
                QString machineId = cmdDetail[0].right(3);
                QString wasteId = machineId + QDate::currentDate().toString("yyyyMMdd") + cmdDetail[1].right(8);
                sql = tr("select * from orderinfo where wasteid = '%1'").arg(wasteId);
                query = getSqlManager()->ExecQuery(sql);
                if(query != NULL)
                {
                    if(!query->next())
                    {
                        //��ȡ����Ա���
                        sql = tr("select userid from login where machineid = '%1'").arg(cmdDetail[0].right(3));
                        query = getSqlManager()->ExecQuery(sql);
                        if(query != NULL)
                        {
                            if(query->next())
                            {
                                int userid = query->value(0).toInt();
                                QList<DishesInfo> dishesList;
                                DishesInfo info;

                                QString dissql = "";

                                //��Ӳ�Ʒ
                                for(int i = 2; i < cmdDetail.count(); i++)
                                {
                                    info.id = cmdDetail[i].mid(8, 5).toInt();
                                    info.count = cmdDetail[i].mid(14, 4).toInt();
                                    info.type = 0;
                                    dissql = tr("select dishesname,price,typeid from dishes where dishesid = '%1'").arg(info.id);
                                    QSqlQuery *disquery = getSqlManager()->ExecQuery(dissql);
                                    if(disquery != NULL)
                                    {
                                        if(disquery->next())
                                        {
                                            info.name = disquery->value(0).toString();
                                            info.price = disquery->value(1).toDouble();
                                            info.dishType = disquery->value(2).toInt();
                                        }
                                        qDebug()<<"dishid"<<info.id<<info.name<<info.dishType;
                                    }
                                    dishesList.append(info);
                                }
                                QString orderId = dinnerTableDataInstance()->getOrderByTableId(tableId);
                                double money = 0;
                                qDebug()<<"get userid------------------------"<<userid;
                                bool result = orderHelperInstance()->createOrder(tableId,dishesList, wasteId, userid ,money, orderId);
                                if(result)
                                {
                                    //���ٿ��
                                    //���д�ӡ
                                    result = getBackPrinter()->print(tableId, dishesList, orderId, money);
                                    getFrontPrinter()->print(tableId,dishesList,orderId,userid,money);
                                    if(result)
                                    {
                                        //�ظ�����
                                        replyList.append("��˳ɹ�");
                                        reply(replyList, index);
                                        return;
                                    }

                                }
                                else
                                {
                                    replyList.append("���ʧ��");
                                    reply(replyList, index);
                                    return;
                                }
                            }
                        }


                    }
                    else
                    {
                        replyList.append("�˲˵��ѵ�");
                        reply(replyList, index);
                        return;
                    }
                }
            }
        }
        else
        {
            replyList.append("��̨δ��");
            replyList.append("���ȿ�̨");
            reply(replyList, index);
            return;
        }
    }
    else
    {
        replyList.append("��ʽ����");
        reply(replyList, index);
        return;
    }
    replyList.append("���ʧ��");
    reply(replyList, index);
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
    //        //ȷ���Ѿ���̨
    //        QString tableId = cmdDetail[1].left(7);
    //        tableId = tr("%1").arg(tableId.toInt(), 4, 10, QLatin1Char('0'));
    //        QString sql = tr("select * from diningtable where id = '%1' and state = 1").arg(tableId);
    //        QSqlQuery *query = getSqlManager()->ExecQuery(sql);
    //        if(query != NULL)
    //        {
    //            if(query->next())
    //            {
    //                //��ȡ����Ա���
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
    //                            //���ٿ��
    //                            //���д�ӡ
    //                            //�ظ�����
    //                            replyList.append("�˲˳ɹ�");
    //                            reply(replyList, index);
    //                            return;
    //                        }
    //                        else
    //                        {
    //                            replyList.append("�˲�ʧ��");
    //                            reply(replyList, index);
    //                            return;
    //                        }
    //                    }
    //                }
    //            }
    //            else
    //            {
    //                replyList.append("��̨δ��");
    //                reply(replyList, index);
    //                return;
    //            }
    //        }
    //        else
    //        {
    //            replyList.append("��ѯʧ��");
    //            reply(replyList, index);
    //            return;
    //        }
    //    }
    //    else
    //    {
    //        replyList.append("��ʽ����");
    //        reply(replyList, index);
    //        return;
    //    }

}


LoginHandler::LoginHandler()
{
    connect(this, SIGNAL(updateInfo()), tableWidget(), SLOT(updateLoginInfo()));
}
