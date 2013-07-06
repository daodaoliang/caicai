#include <QtGui/QApplication>
#include "mainwidget.h"
#include <QTextCodec>
#include <QSqlDatabase>
#include <QDebug>
#include "titlewidget.h"
#include "printerwidget.h"
#include "sqlmanager.h"
#include "cardreadermanager.h"
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
    getCardReader()->LoadLibraty();
    //    PrinterWidget testWidget;
    //    testWidget.EnterWidget(&testWidget);
    //    testWidget.show();
    return a.exec();
}
