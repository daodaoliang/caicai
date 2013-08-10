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
    QString m_printerIp2;
    //打印机读写端口
    QString m_writerPort;
    //打印获取状态端口
    QString m_statePort;
    //卡读写器端口
    QString m_cardReaderPort;
    QString m_cardReaderRate;
public:
    bool createInstance();
public:
    QString printerIp();
    QString printerIp2();
    QString writerPort();
    QString statePort();
    QString cardReaderPort();
    QString cardReaderRate();
    void setPrinterIp(const QString &data);
    void setWriterPort(const QString &data);
    void setStatePort(const QString &data);
    void setcardReaderPort(const QString &data);
    void setcardReaderRate(const QString &data);
};
ConfigerFileProcesser *getConfigerFileInstance();
#endif // CONFIGERFILEPROCESSER_H
