#ifndef FILEOPERATE_H
#define FILEOPERATE_H

#include <QObject>
#include <QFile>
#include <QStringList>

enum LogDegree
{
    BOTH=0,
    DEBUG=1,
    LOG=2,
    NONE=3
};

class FileOperate : public QObject
{
    Q_OBJECT
public:
    explicit FileOperate(QObject *parent = 0);

public:
    //生成日志文件
    bool OpenLog();
    //将内容写到文件
    void LogInFile(const QString &msg);
    //获取当前日志文件列表，以便删除及命名
    QStringList GetLogFileList();
    //当文件个数超过m_LogNum，删除Log1
    bool DeleteLog();
    void RenameLogList(const QStringList &LogList);
    //设置日至文件名
    bool SetFileName(const QString &filename);
    void SetFilePath(const QString & filePath);
    //设置日志等级
    void SetLogDegree(LogDegree degree);
    //获得日志文件名
    QString GetFileName();
    //从配置文件读取配置项
    void ReadSettings();
    //获得日志的最大大小
    int GetLogMaxSize();
    //修改日志文件名，将如a.log修改为a.1.log,并重新创建a.log
    void RenameLog();
    void LogMsg(const QString &msg);
    bool InitLog(const QString &name);

private:
    int m_LogNum;
    int m_LogSize;
    QString m_LogName;
    //日志文件的名称如lane.log中的lane;
    QString m_bakName;
    QString m_LogPath;
    LogDegree m_degree;
    QFile m_File;
    bool m_bIsInit;

};
FileOperate* getLog();
#endif // FILEOPERATE_H
