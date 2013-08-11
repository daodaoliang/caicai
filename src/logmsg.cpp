#include "logmsg.h"
//#include "../MiniLog/minilog.h"
Logger::Logger(QObject *parent) :
    QObject(parent)
{
}
Logger* getLogMsg()
{
    static QMutex mutexn;
    QMutexLocker lock(&mutexn);
    static Logger* log = NULL;
    if(log == NULL)
    {
        log = new Logger();
    }
    return log;
}
//bool LogMsg::loadLogLib()
//{
//    QString sLibFileName = "MiniLog.dll";
//    m_LogoLib.setFileName(sLibFileName);
//    if(!m_LogoLib.load())
//    {
//        return false;
//    }
//    m_pInitLog=(pFunInitLog)m_LogoLib.resolve("InitLog");
//    m_pLogMsg=(pFunLogMsg)m_LogoLib.resolve("LogMsg");
//    if(m_pInitLog == NULL || m_pLogMsg == NULL)
//    {
//        return false;
//    }
//    return true;
//}

bool Logger::InitLog(QString fileName)
{
    //return ::InitLog(fileName);
    return m_Log.InitLog(fileName);
}

void Logger::iLogMsg(QString msg)
{
    QMutexLocker lock(&mutex);
    //::LogMsg(msg, LOG);
    m_Log.LogMsg(msg);
}

bool Logger::SetLogPath(QString filePath)
{
    //return ::SetLogPath(filePath);
    m_Log.SetFilePath(filePath);
}
