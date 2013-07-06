#ifndef CARDREADERMANAGER_H
#define CARDREADERMANAGER_H

#include <QObject>
#include <QLibrary>
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
    bool LoadKey(unsigned char Mode,unsigned char SecNr,unsigned char *NKey);
    bool AuthenticationCard(unsigned char Mode,unsigned char SecNr);
    bool ReadCard();
signals:
    
public slots:
private:
    QLibrary m_CardReaderLib;
    QString m_LibName;
    int m_DeviceID;
private:
    typedef int _stdcall (*lib_ver) (unsigned char* buffer);
    lib_ver m_Lib_ver;
    typedef int _stdcall (*rf_init) (int port,long baud);
    rf_init m_rf_init;
    typedef int _stdcall (*rf_beep) (int icdev,unsigned int mesc);
    rf_beep m_rf_beep;
    typedef int _stdcall (*rf_display) (int icdev,unsigned char pt_model,short digit);
    rf_display m_rf_display;
    typedef int _stdcall (*rf_get_status) (int icdev,unsigned char *Status);
    rf_get_status m_rf_get_status;
    typedef int _stdcall (*rf_request) (int icdev,unsigned char Mode,unsigned int *TagType);
    rf_request m_rf_request;
    typedef int _stdcall (*rf_anticoll) (int icdev,unsigned char Bcnt,unsigned long *Snr);
    rf_anticoll m_rf_anticoll;
    typedef int _stdcall(*rf_select)(int icdev,unsigned long Snr,unsigned char *Size);
    rf_select m_rf_select;
    typedef int _stdcall (*rf_load_key) (int icdev,unsigned char Mode,unsigned char SecNr,unsigned char *NKey);
    rf_load_key m_rf_load_key;
    typedef int _stdcall (*rf_authentication) (int icdev,unsigned char Mode,unsigned char _SecNr);
    rf_authentication m_rf_authentication;
    typedef int _stdcall (*rf_reset) (int icdev,unsigned int Msec);
    rf_reset m_rf_reset;
    typedef int _stdcall(*rf_exit) (int icdev);
    rf_exit m_rf_exit;
};
CardReaderManager* getCardReader();
#endif // CARDREADERMANAGER_H
