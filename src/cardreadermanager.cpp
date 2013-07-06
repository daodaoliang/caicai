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
    m_getLib_ver = (lib_ver)m_CardReaderLib.resolve("lib_ver");

    return true;
}
