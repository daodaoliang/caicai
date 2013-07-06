#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDateTime>
class SqlManager : public QObject
{
    Q_OBJECT
public:
    explicit SqlManager(QObject *parent = 0);
    bool Init();
    bool InsertVipInfo(QString cardID,QString name,QString phone,QString idCard,QDateTime startTime,QDateTime expireTime,int memTypeid,QString shopID);
    bool DelVipInfo(QString cardID);
    bool UpdateVipInfo(QString name,QString phone,QString idCard,QDateTime expireTime,int memTypeid,QString shopID);
    bool ExecQuery(QSqlQuery &query, QString sql);
signals:
    
public slots:
private:
    QSqlDatabase m_DB;
    QString m_DBName;
    QString m_HostName;
    QString m_UserName;
    QString m_Password;
};
SqlManager* getSqlManager();
#endif // SQLMANAGER_H
