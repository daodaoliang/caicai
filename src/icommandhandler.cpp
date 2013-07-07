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
        password = QCryptographicHash::hash(tr("%1%2").arg(user).arg(password).toLocal8Bit(), QCryptographicHash::Md5).toHex().data();
        QString sql = tr("select nickname from user where username = '%1' and password = '%2'").arg(user).arg(password);
        qDebug() << sql;
        QSqlQuery *query = getSqlManager()->ExecQuery(sql);
        if(query != NULL)
        {
            if(query->next())
            {
                QString nickName = query->value(0).toString();
                replyList.append(tr("1 %1").arg(nickName));
                reply(replyList, index);
                return;
            }
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
        //人数
        tableId = tr("%1").arg(tableId.toInt(), 4, 10, QLatin1Char('0'));

        int guestNumber = cmdDetail[1].mid(5, 2).toInt();
        QString waiterId = cmdDetail[1].right(5);
        QString sql = tr("update diningtable set state = 1, guestnumber = %1, waiterid = %2 where id = '%3' and state = 0")
                .arg(guestNumber).arg(waiterId).arg(tableId);
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

}


void MessageHandler::handleCommand(const QStringList &cmdDetail, int index)
{
    qDebug() << cmdDetail;

}


void BackDishHandler::handleCommand(const QStringList &cmdDetail, int index)
{
    qDebug() << cmdDetail;

}
