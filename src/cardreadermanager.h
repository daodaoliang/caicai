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
};
CardReaderManager* getCardReader();
#endif // CARDREADERMANAGER_H
