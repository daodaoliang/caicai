#ifndef LOGMSG_H
#define LOGMSG_H
#include <QLibrary>
#include <QObject>
#include <QMutexLocker>
#include <QMutex>
#include "fileoperate.h"
class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = 0);
    bool InitLog(QString fileName);
    void iLogMsg(QString msg);
    bool SetLogPath(QString filePath);
signals:
    
public slots:
private:
    QMutex mutex;
    FileOperate m_Log;
};
Logger* getLogMsg();
#endif // LOGMSG_H
