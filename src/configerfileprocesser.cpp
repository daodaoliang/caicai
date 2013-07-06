#include "configerfileprocesser.h"
#include <QSettings>
#include <QFile>
ConfigerFileProcesser::ConfigerFileProcesser(QObject *parent) :
    QObject(parent)
{

}

bool ConfigerFileProcesser::createInstance()
{
    QString tempPath="./dinner.ini";
    if(!QFile::exists(tempPath))
    {
        QFile tempFile(tempPath);
        if(!tempFile.open(QIODevice::ReadWrite))
            return false;
        if(tempFile.readAll().isEmpty())
        {
            QSettings tempSetting(tempPath,QSettings::IniFormat);
            QString tempGroup=tr("Printer");
            tempSetting.setValue(tempGroup+"/printerIp",tr("192.168.123.100"));
            tempSetting.setValue(tempGroup+"/writerPort",tr("9100"));
            tempSetting.setValue(tempGroup+"/statePort",tr("4000"));
        }
    }
    QSettings tempSetting(tempPath,QSettings::IniFormat);

    QString tempGroup=tr("Printer");
    setPrinterIp(tempSetting.value(tempGroup+"/printerIp",tr("192.168.123.100")).toString());
    setWriterPort(tempSetting.value(tempGroup+"/writerPort",tr("9100")).toString());
    setStatePort(tempSetting.value(tempGroup+"/statePort",tr("4000")).toString());
}

QString ConfigerFileProcesser::printerIp()
{
    return m_printerIp;
}

QString ConfigerFileProcesser::writerPort()
{
    return m_writerPort;
}

QString ConfigerFileProcesser::statePort()
{
    return m_statePort;
}

void ConfigerFileProcesser::setPrinterIp(const QString &data)
{
    m_printerIp=data;
}

void ConfigerFileProcesser::setWriterPort(const QString &data)
{
    m_writerPort=data;
}

void ConfigerFileProcesser::setStatePort(const QString &data)
{
    m_statePort=data;
}

ConfigerFileProcesser *getConfigerFileInstance()
{
    static ConfigerFileProcesser myConfigInstance;
    return &myConfigInstance;
}
