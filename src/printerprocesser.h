#ifndef PRINTERPROCESSER_H
#define PRINTERPROCESSER_H

#include <QObject>
#include <QTcpSocket>
class PrinterProcesser : public QObject
{
    Q_OBJECT
public:
    explicit PrinterProcesser(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // PRINTERPROCESSER_H
