#include "printerprocesser.h"
#include "configerfileprocesser.h"
#include <QDebug>
PrinterProcesser::PrinterProcesser(QObject *parent) :
    QObject(parent)
{
    //����ʵ��
    pSocketInstance=new QTcpSocket(this);
    m_timer.start(10000);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(slotReOpenDev()));
    flag=false;
}

void PrinterProcesser::creatPrinterInstance()
{
    //��������
    pSocketInstance->setObjectName(tr("daodaoliang"));
    pSocketInstance->abort();
    pSocketInstance->connectToHost(getConfigerFileInstance()->printerIp(),getConfigerFileInstance()->writerPort().toUInt(),QIODevice::ReadWrite);
    connect(pSocketInstance,SIGNAL(readyRead()),this,SLOT(slotReadMsg()));
    connect(pSocketInstance,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(slotStateChanged(QAbstractSocket::SocketState)));
    connect(pSocketInstance,SIGNAL(connected()),this,SLOT(slotChangeFlag()));
    qDebug()<<getConfigerFileInstance()->printerIp();
    qDebug()<<getConfigerFileInstance()->writerPort();
}

void PrinterProcesser::slotReadMsg()
{
    qDebug()<<pSocketInstance->readAll().toHex().data();
}

void PrinterProcesser::slotStateChanged(QAbstractSocket::SocketState data)
{
    switch (data)
    {
    case QAbstractSocket::UnconnectedState:
        emit signalStateChanged(tr("δ����"));
        flag=false;
        break;
    case QAbstractSocket::HostLookupState:
        emit signalStateChanged(tr("���ڲ�ѯ������"));
        break;
    case QAbstractSocket::ConnectingState:
        emit signalStateChanged(tr("�������ӡ�����"));
        break;
    case QAbstractSocket::BoundState:
        emit signalStateChanged(tr("δ֪"));
        break;
    case QAbstractSocket::ListeningState:
        break;
    case QAbstractSocket::ClosingState:
        emit signalStateChanged(tr("���ڹرա�����"));
        flag=false;
        break;
    default:
        break;
    }
    qDebug()<<"printer ---- state changed"<<data;
}

bool PrinterProcesser::slotWriteMsg(const QString &data)
{
    if(!pSocketInstance->isWritable())
        return false;
    QString tempdata(data);
    tempdata.append(0x0a);
    return pSocketInstance->write(tempdata.toLocal8Bit().toHex())>0;
}

void PrinterProcesser::slotReOpenDev()
{
    qDebug()<<"printer reconnect.............";
    if(!pSocketInstance->isValid())
    {
        qDebug()<<"printer reconnect.............heihei";
        creatPrinterInstance();
        return;
    }
    if(!flag)
    {
        qDebug()<<"printer reconnect.............ok";
        pSocketInstance->setObjectName(tr("daodaoliang"));
        pSocketInstance->connectToHost(getConfigerFileInstance()->printerIp(),getConfigerFileInstance()->writerPort().toUInt(),QIODevice::ReadWrite);

    }
}

void PrinterProcesser::slotChangeFlag()
{
    flag=true;
}

PrinterProcesser *getPrinterInstance()
{
    static PrinterProcesser printerInstance;
    return &printerInstance;
}
