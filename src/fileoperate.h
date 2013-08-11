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
    //������־�ļ�
    bool OpenLog();
    //������д���ļ�
    void LogInFile(const QString &msg);
    //��ȡ��ǰ��־�ļ��б��Ա�ɾ��������
    QStringList GetLogFileList();
    //���ļ���������m_LogNum��ɾ��Log1
    bool DeleteLog();
    void RenameLogList(const QStringList &LogList);
    //���������ļ���
    bool SetFileName(const QString &filename);
    void SetFilePath(const QString & filePath);
    //������־�ȼ�
    void SetLogDegree(LogDegree degree);
    //�����־�ļ���
    QString GetFileName();
    //�������ļ���ȡ������
    void ReadSettings();
    //�����־������С
    int GetLogMaxSize();
    //�޸���־�ļ���������a.log�޸�Ϊa.1.log,�����´���a.log
    void RenameLog();
    void LogMsg(const QString &msg);
    bool InitLog(const QString &name);

private:
    int m_LogNum;
    int m_LogSize;
    QString m_LogName;
    //��־�ļ���������lane.log�е�lane;
    QString m_bakName;
    QString m_LogPath;
    LogDegree m_degree;
    QFile m_File;
    bool m_bIsInit;

};
FileOperate* getLog();
#endif // FILEOPERATE_H
