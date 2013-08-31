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
#include "configerfileprocesser.h"
#include "logmsg.h"
#include <QDir>
//#include "qwt_plot.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    getSqlManager()->Init();
    qApp->setProperty("name", "家乐福店");
    getConfigerFileInstance()->createInstance();
    QString path = QDir::currentPath() + "/log";
    getLogMsg()->SetLogPath(path);
    getLogMsg()->InitLog("restaurant");
    //用户登录
    LoginWidget login;
    login.setAuthType(LoginWidget::Login);
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
    w.showMaximized();
    getCardReader()->LoadLibraty();
    getCardReader()->InitDevice(getConfigerFileInstance()->cardReaderPort().toInt(),getConfigerFileInstance()->cardReaderRate().toLong());
    //    PrinterWidget testWidget;
    //    testWidget.EnterWidget(&testWidget);
    //    testWidget.show();
//    VipWidget vip;
//    vip.show();
    //处理消息
    WindowsEventHandler handler;
    //QwtPlot plot;
    //plot.show();
    return a.exec();
}
