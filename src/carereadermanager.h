#ifndef CAREREADERMANAGER_H
#define CAREREADERMANAGER_H

#include <QObject>
#include <QLibrary>
class CareReaderManager : public QObject
{
    Q_OBJECT
public:
    explicit CareReaderManager(QObject *parent = 0);
    
signals:
    
public slots:
private:
    QLibrary m_CardReaderLib;
    QString m_LibName;
    bool LoadLibrary(QString libName);
    
};

#endif // CAREREADERMANAGER_H
