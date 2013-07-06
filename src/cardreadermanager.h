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
signals:
    
public slots:
private:
    QLibrary m_CardReaderLib;
    QString m_LibName;
    
private:
    typedef int _stdcall (*lib_ver) (unsigned char* buffer);
    lib_ver m_getLib_ver;
    typedef  int _stdcall (*rf_init) (int port,long baud);
    rf_init m_rf_init;
};
CardReaderManager* getCardReader();
#endif // CARDREADERMANAGER_H
