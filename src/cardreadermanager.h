#ifndef CARDREADERMANAGER_H
#define CARDREADERMANAGER_H

#include <QObject>
#include <QLibrary>
#include <windows.h>
class CardReaderManager : public QObject
{
    Q_OBJECT
public:
    explicit CardReaderManager(QObject *parent = 0);
    bool LoadLibraty();
    bool InitDevice(int com,long baud);
    void ExitDevice(int com);
    bool DevBeep(unsigned int mesc);
    bool DevDiaplay(unsigned char model,short digit);
    bool GetStatus(unsigned char *Status);
    bool Reset(unsigned int Msec);
    bool RequestCard(unsigned char model,unsigned int *type);
    bool AnticollCard(unsigned char Bcnt,unsigned long *Snr);
    bool SelectCard(unsigned long Snr,unsigned char *Size);
    bool LoadKey(unsigned char KeyMode,unsigned char SecNr,unsigned char *NKey);
    bool AuthenticationCard(unsigned char Mode,unsigned char SecNr);
    bool ReadCard(unsigned char Adr,unsigned char *Data);
    bool WriteCard(unsigned char Adr,unsigned char *Data);
    bool Halt();
    bool ReadCard(const QString readKey, const int readAdr, char *readData, int readLen);
    bool WriteCard(const QString writeKey, const int writeAdr, char *writeData, int writeLen);
signals:
    
public slots:
private:
    QLibrary m_CardReaderLib;
    QString m_LibName;
    int m_DeviceID;
    long m_Snr;
private:
    typedef qint16 __stdcall (*lib_ver) (unsigned char* buffer);
    lib_ver m_Lib_ver;
    typedef qint16 __stdcall (*rf_init) (qint16 port,long baud);
    rf_init m_rf_init;
    typedef qint16 __stdcall (*rf_beep) (qint16 icdev,unsigned int mesc);
    rf_beep m_rf_beep;
    typedef qint16 __stdcall (*rf_display) (qint16 icdev,unsigned char pt_model,short digit);
    rf_display m_rf_display;
    typedef qint16 __stdcall (*rf_get_status) (qint16 icdev,unsigned char *Status);
    rf_get_status m_rf_get_status;
    typedef qint16 __stdcall (*rf_request) (qint16 icdev,unsigned char Mode,unsigned int *TagType);
    rf_request m_rf_request;
    typedef qint16 __stdcall (*rf_anticoll) (qint16 icdev,unsigned char Bcnt,unsigned long *Snr);
    rf_anticoll m_rf_anticoll;
    typedef qint16 __stdcall (*rf_select)(qint16 icdev,unsigned long Snr,unsigned char *Size);
    rf_select m_rf_select;
    typedef qint16 __stdcall (*rf_load_key) (qint16 icdev,unsigned char Mode,unsigned char SecNr,unsigned char *NKey);
    rf_load_key m_rf_load_key;
    typedef qint16 __stdcall (*rf_authentication) (qint16 icdev,unsigned char Mode,unsigned char SecNr);
    rf_authentication m_rf_authentication;
    typedef qint16 __stdcall (*rf_reset) (qint16 icdev,quint16 Msec);
    rf_reset m_rf_reset;
    typedef qint16 __stdcall (*rf_exit) (qint16 icdev);
    rf_exit m_rf_exit;
    typedef qint16 __stdcall (*rf_read) (qint16 icdev,unsigned char Adr,unsigned char *Data);
    rf_read m_rf_read;
    typedef qint16 __stdcall (*rf_halt) (qint16 icdev);
    rf_halt m_rf_halt;
    typedef qint16 __stdcall (*rf_write) (qint16 icdev,unsigned char Adr,unsigned char *Data);
    rf_write m_rf_write;
};
CardReaderManager* getCardReader();
#endif // CARDREADERMANAGER_H
