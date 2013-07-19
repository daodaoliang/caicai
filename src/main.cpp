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
#include "loginwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    getSqlManager()->Init();
    qApp->setProperty("name", "洪楼店");
    //用户登录
    LoginWidget login;
    if(!login.exec())
    {
        a.quit();
        return 0;
    }
//    QPalette palette;
//    palette.setColor(QPalette::WindowText,Qt::white);
//    a.setPalette(palette);
    mainWidget w;
    w.show();
    getCardReader()->LoadLibraty();
    getCardReader()->InitDevice(2,115200);
    //    PrinterWidget testWidget;
    //    testWidget.EnterWidget(&testWidget);
    //    testWidget.show();
//    VipWidget vip;
//    vip.show();
    //处理消息
    WindowsEventHandler handler;
    return a.exec();
}
