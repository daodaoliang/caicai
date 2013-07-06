#include "sqlmanager.h"
#include <QDebug>
#include <QSqlQuery>
SqlManager::SqlManager(QObject *parent) :
    QObject(parent)
{
    m_DBName = "localhost";
    m_HostName = "127.0.0.1";
    m_Password = "";
    m_UserName = "root";
}
SqlManager* getSqlManager()
{
    static SqlManager sqlManager;
    return &sqlManager;
}
bool SqlManager::Init()
{
    m_DB.addDatabase("QMYSQL");
    m_DB.setHostName(m_HostName);
    m_DB.setDatabaseName(m_DBName);
    m_DB.setUserName(m_UserName);
    m_DB.setPassword(m_Password);
    if(!m_DB.open())
    {
        qDebug()<<tr("MySql Open False");
        return false;
    }
}

bool SqlManager::InsertVipInfo(QString cardID, QString name, QString phone, QString idCard, QDateTime startTime, QDateTime expireTime, int memTypeid, QString shopID)
{
    QString sql = tr("insert into member (cardid,name,phone,idcard,starttime,expiretime,membertypeid,shopid values (?,?,?,?,?,?,?,?,?)");
    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(cardID);
    query.addBindValue(name);
    query.addBindValue(phone);
    query.addBindValue(idCard);
    query.addBindValue(startTime);
    query.addBindValue(expireTime);
    query.addBindValue(memTypeid);
    query.addBindValue(shopID);
    if(query.exec())
    {
        return true;
    }
    return false;
}

bool SqlManager::DelVipInfo(QString cardID)
{
    QString sql = tr("delete from memeber where cardid = '%1'").arg(cardID);
    QSqlQuery query(sql);
    if(query.exec())
    {
        return true;
    }
    return false;
}

bool SqlManager::UpdateVipInfo(QString name, QString phone, QString idCard, QDateTime expireTime, int memTypeid, QString shopID)
{
    QString sql = tr("insert into member (name,phone,idcard,starttime,expiretime,membertypeid,shopid values (?,?,?,?,?,?,?,?)");
    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(name);
    query.addBindValue(phone);
    query.addBindValue(idCard);
    query.addBindValue(expireTime);
    query.addBindValue(memTypeid);
    query.addBindValue(shopID);
    if(query.exec())
    {
        return true;
    }
    return false;
}