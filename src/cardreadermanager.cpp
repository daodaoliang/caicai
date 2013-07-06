#include "cardreadermanager.h"

CardReaderManager::CardReaderManager(QObject *parent) :
    QObject(parent)
{
    m_LibName = "./mwrf32.dll";
}

bool CardReaderManager::LoadLibraty()
{
    m_CardReaderLib.setFileName(m_LibName);
    if(!m_CardReaderLib.load())
    {
        return false;
    }
    return true;
}
