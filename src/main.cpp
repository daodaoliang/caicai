#include <QtGui/QApplication>
#include "mainwidget.h"
#include <QTextCodec>
#include <QSqlDatabase>
#include <QDebug>
#include "titlewidget.h"
#include "printerwidget.h"
#include "sqlmanager.h"
#include "windowseventhandler.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::white);
    a.setPalette(palette);
    mainWidget w;
    w.show();
    getSqlManager()->Init();
    PrinterWidget testWidget;
    testWidget.EnterWidget(&testWidget);
    testWidget.show();
    //处理消息
    WindowsEventHandler handler;
    getSqlManager()->Init();
    return a.exec();
}
