#include "cardreadermanager.h"
#include <QDebug>
CardReaderManager::CardReaderManager(QObject *parent) :
    QObject(parent)
{
    m_LibName = "./mwrf32.dll";
    m_DeviceID = 0;
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
    m_rf_read = NULL;
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
    m_rf_read = (rf_read)m_CardReaderLib.resolve("rf_read");
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
    qint16 ret;
    qDebug()<<ret;
    ret = m_rf_beep(m_DeviceID,mesc);
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
    int ret;
    qDebug()<<ret;
    ret = m_rf_reset(m_DeviceID,Msec);
    if( ret!= 0)
    {
        qDebug()<<"m_rf_reset 0"<<m_DeviceID<<":"<<ret;
        return false;
    }
    else
    {
        qDebug() << "reset success";
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
    int ret = m_rf_request(m_DeviceID,model,type);
    if( ret!= 0)
    {
        qDebug()<<"request 0"<<ret;
        return false;
    }
    qDebug()<<"request ret"<<ret;
    return true;
}

bool CardReaderManager::AnticollCard(unsigned char Bcnt, unsigned long *Snr)
{
    if(m_rf_anticoll == NULL)
    {
        return false;
    }
    int ret = m_rf_anticoll(m_DeviceID,Bcnt,Snr);
    if( ret!= 0)
    {
        qDebug()<<"AnticollCard"<<ret;
        return false;
    }
    qDebug()<<"AnticollCard ret"<<ret;
    return true;
}

bool CardReaderManager::SelectCard(unsigned long Snr, unsigned char *Size)
{
    if(m_rf_select == NULL)
    {
        return false;
    }
    int ret = m_rf_select(m_DeviceID,Snr,Size);
    if( ret!= 0)
    {
        qDebug()<<"SelectCard"<<ret;
        return false;
    }
    qDebug()<<"selectcard ret"<<ret;
    return true;
}

bool CardReaderManager::LoadKey(unsigned char KeyMode, unsigned char SecNr, unsigned char *NKey)
{
    if(m_rf_load_key == NULL)
    {
        return false;
    }
    int ret = m_rf_load_key(m_DeviceID,KeyMode,SecNr,NKey);
    if(ret != 0)
    {
        qDebug()<<"LoadKey"<<ret;
        return false;
    }
    qDebug()<<"loadkey ret"<<ret;
    return true;
}

bool CardReaderManager::AuthenticationCard(unsigned char Mode, unsigned char SecNr)
{
    if(m_rf_authentication == NULL)
    {
        return false;
    }
    qint16 ret = m_rf_authentication(m_DeviceID,Mode,SecNr);
    if(ret!= 0)
    {
        qDebug()<<"AuthenticationCard ret"<<ret;
        return false;
    }
    qDebug()<<"AuthenticationCard ret"<<ret;
    return true;
}

bool CardReaderManager::ReadCard(unsigned char Adr, unsigned char *Data)
{
    if(m_rf_read == NULL)
    {
        return false;
    }
    int ret = m_rf_read(m_DeviceID,Adr,Data);
    if( ret!= 0)
    {
        qDebug()<<"ReadCard 0"<<ret;
        return false;
    }
    qDebug()<<tr("ReadCard ret%1").arg(ret);

    return true;
}

bool CardReaderManager::ReadCard()
{
    unsigned int type = 0x0004;
    unsigned long snr;
    unsigned char size;
    unsigned char key[12];
    memset(key,0,12);
    char kkey[12] = {'f','f','f','f','f','f','f','f','f','f','f','f'};
    //char kkey[12] = {'1','f','f','f','f','f','f','f','f','f','f','0'};
    unsigned char data[16];
    memcpy(key,kkey,12);
    Reset(10);
    RequestCard(0,&type);
    AnticollCard(0,&snr);
    SelectCard(snr,&size);
    LoadKey(0,1,key);
    AuthenticationCard(0,2);
    ReadCard(9,data);
    char ndata[16];
    memset(ndata,0,16);
    memcpy(ndata,data,16);
    qDebug()<<snr<<":"<<size<<"data:"<<QString::fromLocal8Bit(ndata,16);
}

bool CardReaderManager::Write()
{
}
