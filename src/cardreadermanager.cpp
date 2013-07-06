#include "cardreadermanager.h"
#include <QDebug>
CardReaderManager::CardReaderManager(QObject *parent) :
    QObject(parent)
{
    m_LibName = "./mwrf32.dll";
    m_DeviceID = -1;
    m_Lib_ver = NULL;
    m_rf_init = NULL;
    m_rf_beep = NULL;
    m_rf_display = NULL;
    m_rf_get_status = NULL;
    m_rf_request  = NULL;
    m_rf_anticoll = NULL;
    m_rf_select = NULL;
    m_rf_load_key = NULL;
    m_rf_authentication = NULL;
    m_rf_reset = NULL;
    m_rf_exit = NULL;
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
    m_Lib_ver = (lib_ver)m_CardReaderLib.resolve("lib_ver");
    m_rf_display = (rf_display)m_CardReaderLib.resolve("rf_disp");
    m_rf_get_status = (rf_get_status)m_CardReaderLib.resolve("rf_get_status");
    m_rf_init = (rf_init)m_CardReaderLib.resolve("rf_init");
    m_rf_beep = (rf_beep)m_CardReaderLib.resolve("rf_beep");
    m_rf_reset = (rf_reset)m_CardReaderLib.resolve("rf_reset");
    m_rf_request = (rf_request)m_CardReaderLib.resolve("rf_request");
    m_rf_anticoll = (rf_anticoll)m_CardReaderLib.resolve("rf_anticoll");
    m_rf_select = (rf_select)m_CardReaderLib.resolve("rf_select");
    m_rf_load_key = (rf_load_key)m_CardReaderLib.resolve("rf_load_key");
    m_rf_authentication = (rf_authentication)m_CardReaderLib.resolve("rf_authentication");
    m_rf_exit = (rf_exit)m_CardReaderLib.resolve("rf_exit");
    return true;
}

bool CardReaderManager::InitDevice(int com,long baud)
{
    ExitDevice(com);
    //³õÊ¼»¯²âÊÔ
    if(m_rf_init == NULL)
    {
        qDebug()<<"error";
        return false;
    }
    m_DeviceID = m_rf_init(com,baud);
    if(m_DeviceID <= 0)
    {
        return false;
    }
    return true;
}

void CardReaderManager::ExitDevice(int com)
{
    if(m_rf_exit == NULL)
    {
        qDebug()<<"exit null";
        return;
    }
    m_rf_exit(com);
}

bool CardReaderManager::DevBeep(unsigned int mesc)
{
    qDebug()<<"beep start";
    if(m_rf_beep == NULL)
    {
        return false;
    }
    int ret = m_rf_beep(m_DeviceID,mesc);
    if(ret != 0)
    {
        qDebug()<<"beep "<<ret;
        return false;
    }
    qDebug()<<"beep end"<<m_DeviceID;
    return true;
}

bool CardReaderManager::DevDiaplay(unsigned char model, short digit)
{
    if(m_rf_display == NULL)
    {
        qDebug()<<"m_rf_display null";
        return false;
    }
    if(m_rf_display(m_DeviceID,model,digit) != 0)
    {
        qDebug()<<"m_rf_display 0";
        return false;
    }
    return true;
}

bool CardReaderManager::GetStatus(unsigned char *Status)
{
    if(m_rf_get_status == NULL)
    {
        qDebug()<<"m_rf_get_status null";
        return false;
    }
    if(m_rf_get_status(m_DeviceID,Status) != 0)
    {
        qDebug()<<"m_rf_get_status 0";
        return false;
    }
    return true;
}

bool CardReaderManager::Reset(unsigned int Msec)
{
    if(m_rf_reset == NULL)
    {
        qDebug()<<"m_rf_reset null";
        return false;
    }
    int ret = m_rf_reset(m_DeviceID,Msec);
    if( ret!= 0)
    {
        qDebug()<<"m_rf_reset 0"<<m_DeviceID<<":"<<ret;
        return false;
    }
    return true;
}

bool CardReaderManager::RequestCard(unsigned char model,unsigned int* type)
{
    if(m_rf_request == NULL)
    {
        qDebug()<<"request null";
        return false;
    }
    unsigned int ty = 0x0004;
    if(m_rf_request(m_DeviceID,0,&ty) != 0)
    {
        qDebug()<<"request 0";
        return false;
    }
    return true;
}

bool CardReaderManager::AnticollCard(unsigned char Bcnt, unsigned long *Snr)
{
    if(m_rf_anticoll == NULL)
    {
        return false;
    }
    if(m_rf_anticoll(m_DeviceID,Bcnt,Snr) != 0)
    {
        return false;
    }
    return true;
}

bool CardReaderManager::SelectCard(unsigned long Snr, unsigned char *Size)
{
    if(m_rf_select == NULL)
    {
        return false;
    }
    if(m_rf_select(m_DeviceID,Snr,Size) != 0)
    {
        return false;
    }
    return true;
}

bool CardReaderManager::LoadKey(unsigned char Mode, unsigned char SecNr, unsigned char *NKey)
{
    if(m_rf_load_key == NULL)
    {
        return false;
    }
    if(m_rf_load_key(m_DeviceID,Mode,SecNr,NKey) != 0)
    {
        return false;
    }
    return true;
}

bool CardReaderManager::AuthenticationCard(unsigned char Mode, unsigned char SecNr)
{
    if(m_rf_authentication == NULL)
    {
        return false;
    }
    if(m_rf_authentication(m_DeviceID,Mode,SecNr) != 0)
    {
        return false;
    }
    return true;
}

bool CardReaderManager::ReadCard()
{
    unsigned char IDLE = 0x00;
    unsigned int type;
    if(!Reset(60))
    {
        qDebug()<<"reset fail";
        return false;
    }
    if(!RequestCard(1,&type))
    {
        qDebug()<<"request card fail";
        return false;
    }
    qDebug()<<"request card seccess";
}
