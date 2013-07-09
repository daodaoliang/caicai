#include <QtGui/QApplication>
#include "mainwidget.h"
#include <QTextCodec>
#include <QSqlDatabase>
#include <QDebug>
#include "titlewidget.h"
#include "printerwidget.h"
#include "sqlmanager.h"
#include "cardreadermanager.h"
#include "windowseventhandler.h"
#include "vipwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    getSqlManager()->Init();

    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::white);
    a.setPalette(palette);
    mainWidget w;
    w.show();
    getCardReader()->LoadLibraty();
    getCardReader()->InitDevice(2,115200);
    QString key = "ffffffffffff";
    QString wdata = "dddd";
    getCardReader()->WriteCard(key,13,wdata.toLocal8Bit().data(),wdata.length());
    //
    char rdata[16];
    getCardReader()->ReadCard(key,13,rdata,wdata.length());
    qDebug()<<"read:"<<QString::fromLocal8Bit(rdata,wdata.length());
    //    PrinterWidget testWidget;
    //    testWidget.EnterWidget(&testWidget);
    //    testWidget.show();

    //    PrinterWidget testWidget;
    //    testWidget.EnterWidget(&testWidget);
    //    testWidget.show();
    VipWidget vip;
    vip.show();
    //处理消息
    WindowsEventHandler handler;
    return a.exec();
}
