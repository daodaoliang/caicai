#ifndef PRINTERPROCESSER_H
#define PRINTERPROCESSER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
struct structCai
{
    //�˵�����
    QString caiName;
    //����
    QString count;
    //����
    QString price;
    //����Ҫ��
    QString spMsg;
};
struct structDinner
{
    //��˾����
    QString sCoName;
    //�ֵ�����
    QString sPartName;
    //����
    QString sZhuo;
    //�˵�
    QList<structCai> listCaicai;
    //ʱ��
    QString time;
};
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
    bool slotWriteMsg(const structDinner& data);
    void slotReOpenDev();
    void slotChangeFlag();
signals:
    void signalStateChanged(QString state);
private:
    //socket  ʵ��
    QTcpSocket *pSocketInstance;
    QTimer m_timer;
    bool flag;
};
PrinterProcesser *getPrinterInstance();
#endif // PRINTERPROCESSER_H
