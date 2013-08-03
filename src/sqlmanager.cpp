#include "sqlmanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QBitArray>
#include <QMessageBox>
SqlManager::SqlManager(QObject *parent) :
    QObject(parent)
{
    m_DBName = "restaurantdb";
    m_HostName = "127.0.0.1";
    m_Password = "";
    m_UserName = "root";
    m_Query = NULL;
}

SqlManager::~SqlManager()
{
    logOut("000");
    delete m_Query;
}
SqlManager* getSqlManager()
{
    static SqlManager sqlManager;
    return &sqlManager;
}
bool SqlManager::Init()
{
    m_DB = QSqlDatabase::addDatabase("QMYSQL","restaurantdb");
    m_DB.setHostName(m_HostName);
    m_DB.setDatabaseName(m_DBName);
    m_DB.setUserName(m_UserName);
    m_DB.setPassword(m_Password);
    if(!m_DB.open())
    {
        qDebug()<<tr("MySql Open False").arg(m_DB.lastError().text());
        return false;
    }
    m_Query = new QSqlQuery(m_DB);
    qDebug()<<"MySql Open Success";
    return true;
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

bool SqlManager::GetVipInfo()
{
    QString sql = tr("select * from memeber");
    QSqlQuery query(sql);
    if(!query.exec())
    {
        return false;
    }
    return true;
}

QString SqlManager::login(const QString &user, QString password, const QString &machineId, int &userId)
{
    qDebug()<<"start log:"<<password;
    password = QCryptographicHash::hash(tr("%1%2").arg(user).arg(password).toLocal8Bit(), QCryptographicHash::Md5).toHex().data();
    QString sql = tr("select nickname, userid, purview from userinfo where username = '%1' and password = '%2' and machineid = ''").arg(user).arg(password);
    qDebug() << sql;
    QSqlQuery *query = getSqlManager()->ExecQuery(sql);

    if(query != NULL)
    {
        if(query->next())
        {
            QByteArray function = query->value(2).toByteArray();
            //高权限登录
            if(machineId == "000")
            {
                if(function.at(0) != 1)
                {
                    return "";
                }
            }
            //更新数据库
            sql = tr("update userinfo set machineid = '%1' where userid = '%2'").arg(machineId).arg(query->value(1).toInt());
            QString nickName = query->value(0).toString();
            int user = query->value(1).toInt();
            QSqlQuery *updateQuery = getSqlManager()->ExecQuery(sql);
            if(updateQuery != NULL)
            {
                if(updateQuery->numRowsAffected() == 1)
                {
                    userId = user;
                    return nickName;
                }
                else
                {
                    return "";
                }
            }
        }
    }
    else
    {
        QMessageBox::information(NULL,"","");
    }
    return "";
}

bool SqlManager::auth(const QString &user, QString password, int authType)
{
    password = QCryptographicHash::hash(tr("%1%2").arg(user).arg(password).toLocal8Bit(), QCryptographicHash::Md5).toHex().data();

    QString sql = tr("select purview from userinfo where username = '%1' and password = '%2'")
            .arg(user).arg(password);
    QSqlQuery query = execQuery(sql);
    if(query.next())
    {
        if(query.value(0).toByteArray().at(authType) == 1)
        {
            return true;
        }
    }
    return false;
}

void SqlManager::logOut(const QString &id)
{
    QString sql = tr("update userinfo set machineid = '' where machineid = '%1'").arg(id);
    ExecQuery(sql);
}

QSqlQuery *SqlManager::ExecQuery(QString sql)
{
    qDebug() << "exec sql is" << sql;
    if(m_Query)
    {
        m_Query->clear();
        if(m_Query->exec(sql))
        {
            return m_Query;
        }
    }
    return NULL;
}

QSqlQuery SqlManager::execQuery(const QString &sql)
{
    qDebug() << sql;
    return m_DB.exec(sql);
}
