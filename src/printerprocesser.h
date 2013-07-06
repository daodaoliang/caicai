#ifndef PRINTERPROCESSER_H
#define PRINTERPROCESSER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
struct structCai
{
    //菜的名字
    QString caiName;
    //份数
    QString count;
    //单价
    QString price;
    //特殊要求
    QString spMsg;
};
struct structDinner
{
    //公司名字
    QString sCoName;
    //分店名字
    QString sPartName;
    //桌号
    QString sZhuo;
    //菜单
    QList<structCai> listCaicai;
    //时间
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
    //socket  实例
    QTcpSocket *pSocketInstance;
    QTimer m_timer;
    bool flag;
};
PrinterProcesser *getPrinterInstance();
#endif // PRINTERPROCESSER_H
