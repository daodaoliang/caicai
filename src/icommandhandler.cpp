#include "icommandhandler.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QStringList>
#include <QApplication>
#include <QFile>
#include "sqlmanager.h"
#include <windows.h>
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
        QString sql = tr("select nickname from user where username = '%1' and password = '%2'");
        QSqlQuery *query = getSqlManager()->ExecQuery(sql);
        if(query != NULL)
        {
            if(query->next())
            {
                QString nickName = query->value(0).toString();
                replyList.append(tr("1 %1").arg(nickName));
                reply(replyList, index);
            }
        }
    }
    replyList.append("0");
    reply(replyList, index);
}


void OpenMachineHandler::handleCommand(const QStringList &cmdDetail, int index)
{
    qDebug() << cmdDetail;

}


void OpenTableHandler::handleCommand(const QStringList &cmdDetail, int index)
{
    qDebug() << cmdDetail;

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
