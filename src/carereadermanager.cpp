#include "carereadermanager.h"

CareReaderManager::CareReaderManager(QObject *parent) :
    QObject(parent)
{
    m_LibName = "./mwrf32.dll";
}

bool CareReaderManager::LoadLibrary(QString libName)
{
    m_CardReaderLib.setFileName(m_LibName);
    if(!m_CardReaderLib.load())
    {
        return false;
    }
}
