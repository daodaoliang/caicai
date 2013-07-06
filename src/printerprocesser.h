#ifndef PRINTERPROCESSER_H
#define PRINTERPROCESSER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
class PrinterProcesser : public QObject
{
    Q_OBJECT
public:
    explicit PrinterProcesser(QObject *parent = 0);
public:
    void creatPrinterInstance();
public slots:
    void slotReadMsg();
    void slotStateChanged(QAbstractSocket::SocketState data);
    bool slotWriteMsg(const QString& data);
    void slotReOpenDev();
    void slotChangeFlag();
signals:
    void signalStateChanged(QString state);
private:
    //socket  实例
    QTcpSocket *pSocketInstance;
    QTimer m_timer;
    bool flag;
};
PrinterProcesser *getPrinterInstance();
#endif // PRINTERPROCESSER_H
