#ifndef CONFIGERFILEPROCESSER_H
#define CONFIGERFILEPROCESSER_H

#include <QObject>

class ConfigerFileProcesser : public QObject
{
    Q_OBJECT
public:
    explicit ConfigerFileProcesser(QObject *parent = 0);
private:
    /********************配置项定义********************/
    //打印机标签（Printer）
    //打印机ＩＰ
    QString m_printerIp;
    //打印机读写端口
    QString m_writerPort;
    //打印获取状态端口
    QString m_statePort;
public:
    bool createInstance();
public:
    QString printerIp();
    QString writerPort();
    QString statePort();
    void setPrinterIp(const QString &data);
    void setWriterPort(const QString &data);
    void setStatePort(const QString &data);
};
ConfigerFileProcesser *getConfigerFileInstance();
#endif // CONFIGERFILEPROCESSER_H
