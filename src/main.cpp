#include <QtGui/QApplication>
#include "mainwidget.h"
#include <QTextCodec>
#include <QSqlDatabase>
#include <QDebug>
#include "titlewidget.h"
<<<<<<< HEAD
#include "printerwidget.h"
=======
#include "sqlmanager.h"
>>>>>>> 3b228b217aa7912381fee3c04ce88c1b25093133
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::white);
    a.setPalette(palette);
<<<<<<< HEAD
    //mainWidget w;
    //w.show();
    PrinterWidget myWidget;
    myWidget.EnterWidget(&myWidget);
    myWidget.show();
=======

  //  a.setFont(QFont());
    mainWidget w;

  //  sysButtonWidget w;
  //  titleWidget w;
    w.show();
    getSqlManager()->Init();
>>>>>>> 3b228b217aa7912381fee3c04ce88c1b25093133
    return a.exec();
}
