#include "fileoperate.h"
#include <QDebug>
#include <QDir>
#include <QTextCodec>
#include <QDateTime>
#include <QSettings>
#include <QDir>
//转换编码方式
QString UTF8toGB2312(QString str, int length = -1)
{
    QByteArray temp;
    temp = QTextCodec::codecForName("GB2312")->fromUnicode(QTextCodec::codecForName("UTF-8")->toUnicode(str.toLocal8Bit()));
    return QString::fromLocal8Bit(temp.constData());
}
FileOperate::FileOperate(QObject *parent) :
    QObject(parent)
{
    //此为定义初值，当无法读取配置文件时使用以下数据
    m_degree = BOTH;
    m_LogNum = 8;
    m_LogSize = 3;
    m_LogPath = QDir::currentPath();
    m_bIsInit = false;
}

bool FileOperate::OpenLog()
{
    bool ret;
    ReadSettings();
    if(m_File.isOpen())
    {
        m_File.close();
    }
    m_File.setFileName(m_LogName);
    ret = m_File.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    return ret;
}

void FileOperate::LogInFile(const QString &msg)
{
    if(!m_File.isOpen())
    {
        if(!OpenLog())
        {
            qDebug()<<QObject::tr("%1日志创建或打开失败").arg(m_LogName);
            return;
        }
    }
    RenameLog();
    QString slogger = QObject::tr("[%1] %2\n")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz"))
            .arg(msg);
    m_File.write(slogger.toLocal8Bit());
    m_File.flush();
}

QStringList FileOperate::GetLogFileList()
{
    QDir tempDir;
    tempDir.setPath(m_LogPath);
    QStringList strlist;
    strlist<<tr("%1_*.log").arg(m_bakName);
    return tempDir.entryList(strlist,QDir::Files,QDir::Name);
}

bool FileOperate::DeleteLog()
{
    if(m_LogNum > GetLogFileList().size())
    {
        return false;
    }
    QString tempStr;
    bool ret;
    tempStr = (m_LogPath+"/"+QObject::tr("%1_1.log").arg(m_bakName));

    ret= QFile::remove(tempStr);
    return ret;
}

bool FileOperate::SetFileName(const QString &filename)
{
    QDir dir;
    //dir.setPath(m_LogPath);
    if(!dir.exists(m_LogPath))
    {
        if(!dir.mkpath(m_LogPath))
        {
            return false;
        }
    }
    m_bakName = filename;
    m_LogName = tr("%1.log").arg(m_LogPath+"/"+filename);
}

void FileOperate::SetFilePath(const QString &filePath)
{
    m_LogPath = filePath;
}
//从配置文件读取配置项
void FileOperate::ReadSettings()
{
    QSettings Settings("./MiniLog.ini",QSettings::IniFormat);
    QString groupName("Settings");
    //m_LogNum = Settings.value("/LogNum",2).toInt();
    //m_LogSize = Settings.value("/LogSize",2).toInt();
    m_degree = (LogDegree)Settings.value("/LogDegree",0).toInt();

}
//获取文件最大大小
int FileOperate::GetLogMaxSize()
{
    return m_LogSize*1024*1024;
}
//
void FileOperate::LogMsg(const QString &msg)
{
    if(!m_bIsInit)
    {
        return;
    }
    SetLogDegree(LOG);
    switch(m_degree)
    {
    case BOTH:
    {
        LogInFile(msg);
        qDebug()<<QObject::tr("%1--%2").arg(m_bakName).arg(msg);
        break;
    }
    case DEBUG:
    {
        qDebug()<<QObject::tr("%1--%2").arg(m_bakName).arg(msg);
        break;
    }
    case LOG:
    {
        LogInFile(msg);
        break;
    }
    default:
        break;
    }
}

bool FileOperate::InitLog(const QString &name)
{
    if(!SetFileName(name))
    {
        m_bIsInit = false;
        return false;
    }
    if(!OpenLog())
    {
        m_bIsInit = false;
        return false;
    }
    m_bIsInit = true;
    return true;
}

QString FileOperate::GetFileName()
{
    return m_LogName;
}

void FileOperate::RenameLog()
{
    //qDebug()<<m_bakName<<"size:"<<m_File.size()<<" "<<"maxsize:"<<GetLogMaxSize();
    bool ret;
    if(m_File.size() > GetLogMaxSize())
    {
        if(DeleteLog())
        {
            RenameLogList(GetLogFileList());
        }
        if(m_File.isOpen())
        {
            m_File.close();
        }
        m_File.rename(m_LogPath+"/"+QObject::tr("%1_%2.log").arg(m_bakName).arg(QString::number(GetLogFileList().size()+1)));
        //文件名中如Lane.log1中1是否正确
        m_File.setFileName(m_LogName);
    }
    if(!m_File.isOpen())
    {
        ret = m_File.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    }
}
FileOperate* getLog()
{
    static FileOperate oper;
    return &oper;
}

void FileOperate::SetLogDegree(LogDegree degree)
{
    m_degree = degree;
}

void FileOperate::RenameLogList(const QStringList &LogList)
{
    for(int i = 2;(i-2) != LogList.size(); ++i )
    {
        QString temp = QString::number(i);
        for(int j = 0; j != LogList.size(); ++j)
        {
            if(LogList.at(j).contains(m_bakName+"_"+temp))
            {
                temp =(m_LogPath+"/"+QObject::tr("%1_%2.log").arg(m_bakName).arg(QString::number(i-1)));
                qDebug()<<"RenameLogList filename...."<<temp;
                QFile::rename(m_LogPath+"/"+LogList.at(j),temp);
                break;
            }
        }
    }
}
