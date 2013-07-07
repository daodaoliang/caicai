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
    bool ReadCard();
    bool Write();
signals:
    
public slots:
private:
    QLibrary m_CardReaderLib;
    QString m_LibName;
    HANDLE m_DeviceID;
    long m_Snr;
private:
    typedef int __stdcall (*lib_ver) (unsigned char* buffer);
    lib_ver m_Lib_ver;
    typedef HANDLE __stdcall (*rf_init) (qint16 port,long baud);
    rf_init m_rf_init;
    typedef int __stdcall (*rf_beep) (HANDLE icdev,unsigned int mesc);
    rf_beep m_rf_beep;
    typedef int __stdcall (*rf_display) (HANDLE icdev,unsigned char pt_model,short digit);
    rf_display m_rf_display;
    typedef int __stdcall (*rf_get_status) (HANDLE icdev,unsigned char *Status);
    rf_get_status m_rf_get_status;
    typedef int __stdcall (*rf_request) (HANDLE icdev,unsigned char Mode,unsigned int *TagType);
    rf_request m_rf_request;
    typedef int __stdcall (*rf_anticoll) (HANDLE icdev,unsigned char Bcnt,unsigned long *Snr);
    rf_anticoll m_rf_anticoll;
    typedef int __stdcall (*rf_select)(HANDLE icdev,unsigned long Snr,unsigned char *Size);
    rf_select m_rf_select;
    typedef int __stdcall (*rf_load_key) (HANDLE icdev,unsigned char Mode,unsigned char SecNr,unsigned char *NKey);
    rf_load_key m_rf_load_key;
    typedef int __stdcall (*rf_authentication) (HANDLE icdev,unsigned char Mode,unsigned char _SecNr);
    rf_authentication m_rf_authentication;
    typedef qint16 __stdcall (*rf_reset) (HANDLE icdev,quint16 Msec);
    rf_reset m_rf_reset;
    typedef int __stdcall (*rf_exit) (qint16 icdev);
    rf_exit m_rf_exit;
    typedef int __stdcall (*rf_read) (HANDLE icdev,unsigned char Adr,unsigned char *Data);
    rf_read m_rf_read;

};
CardReaderManager* getCardReader();
#endif // CARDREADERMANAGER_H
