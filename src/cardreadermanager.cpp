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
    m_rf_halt = NULL;
    m_rf_write = NULL;
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
    m_rf_halt = (rf_halt)m_CardReaderLib.resolve("rf_halt");
    m_rf_write = (rf_write)m_CardReaderLib.resolve("rf_write");
    return true;
}

bool CardReaderManager::InitDevice(int com,long baud)
{
    ExitDevice(com);
    //初始化测试
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
    if(m_rf_beep == NULL)
    {
        return false;
    }
    qint16 ret;
    qDebug()<<ret;
    ret = m_rf_beep(m_DeviceID,mesc);
    if(ret != 0)
    {
        return false;
    }
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

bool CardReaderManager::WriteCard(unsigned char Adr, unsigned char *Data)
{
    if(m_rf_write == NULL)
    {
        return false;
    }
    qint16 ret = m_rf_write(m_DeviceID,Adr,Data);
    if(ret!= 0)
    {
        qDebug()<<"write ret"<<ret;
        return false;
    }
    qDebug()<<"write ret"<<ret;
    return true;
}

bool CardReaderManager::Halt()
{
    if(m_rf_halt == NULL)
    {
        return false;
    }
    int ret = m_rf_halt(m_DeviceID);
    if( ret!= 0)
    {
        qDebug()<<"Halt 0"<<ret;
        return false;
    }
    qDebug()<<tr("Halt ret%1").arg(ret);
    return true;
}

bool CardReaderManager::ReadCard(const QString readKey,const int readAdr,char* readData,int readLen)
{
    unsigned int type = 0x0004;
    //返回卡序列号地址
    unsigned long snr;
    unsigned char size;
    // adr :要读的块号
    //要读的扇区
    int sec = readAdr/4;
    unsigned char key[12];
    memset(key,0,12);
    memcpy(key,readKey.toLocal8Bit().data(),readKey.length());
    unsigned char rdata[16];
    Reset(10);
    RequestCard(1,&type);
    AnticollCard(0,&snr);
    SelectCard(snr,&size);
    LoadKey(0,1,key);
    AuthenticationCard(0,sec);
    ReadCard(readAdr,rdata);
    memcpy(readData,rdata,qMin(readLen,16));
    DevBeep(10);
    Halt();
}

bool CardReaderManager::WriteCard(const QString writeKey,const int writeAdr,char* writeData,int writeLen)
{
    unsigned int type = 0x0004;
    //返回卡序列号地址
    unsigned long snr;
    unsigned char size;
    // adr :要读的块号
    //要写的扇区
    int sec = writeAdr/4;
    unsigned char key[12];
    memset(key,0,12);
    memcpy(key,writeKey.toLocal8Bit().data(),writeKey.length());
    unsigned char wdata[16];
    qDebug()<<"str:"<<QString::fromLocal8Bit(writeData,writeLen)<<"len"<<writeLen;
    QByteArray warry = QByteArray::fromRawData(writeData,writeLen).toHex();
    qDebug()<<"hex:"<<warry<<"wsize:"<<warry.size();
    memcpy(wdata,warry.data(),qMin(16,writeLen));
    Reset(10);
    RequestCard(1,&type);
    AnticollCard(0,&snr);
    SelectCard(snr,&size);
    LoadKey(0,1,key);
    AuthenticationCard(0,sec);
    WriteCard(writeAdr,wdata);
    DevBeep(10);
    Halt();
}
