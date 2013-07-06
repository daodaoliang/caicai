#include <QtGui/QApplication>
#include "mainwidget.h"
#include <QTextCodec>
#include <QSqlDatabase>
#include <QDebug>
#include "titlewidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));
    qDebug() << QSqlDatabase::drivers();
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::white);
    a.setPalette(palette);

  //  a.setFont(QFont());
    mainWidget w;

  //  sysButtonWidget w;
  //  titleWidget w;
    w.show();
    
    return a.exec();
}
