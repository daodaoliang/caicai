#include "cardreadermanager.h"
#include <QDebug>
CardReaderManager::CardReaderManager(QObject *parent) :
    QObject(parent)
{
    m_LibName = "./mwrf32.dll";
    m_getLib_ver = NULL;
}
CardReaderManager* getCardReader()
{
    static CardReaderManager reader;
    return &reader;
}
bool CardReaderManager::LoadLibraty()
{
    m_CardReaderLib.setFileName(m_LibName);
    if(!m_CardReaderLib.load())
    {
        qDebug()<<"CardReader Lib Load Fail";
        return false;
    }
    qDebug()<<"CardReader Lib Load Success";
    //³õÊ¼»¯²âÊÔ
    m_rf_init = (rf_init)m_CardReaderLib.resolve("rf_init");
    if(m_rf_init == NULL)
    {
        qDebug()<<"error";
    }
    qDebug()<<"init:"<<m_rf_init(2,115200);
    //²âÊÔ°æ±¾ºÅ
    m_getLib_ver = (lib_ver)m_CardReaderLib.resolve("lib_ver");
    unsigned char buff[18];
    if(m_getLib_ver(buff) == 0)
    {
        qDebug()<<"version"<<buff;
    }
    qDebug()<<m_getLib_ver(buff);
    return true;
}
