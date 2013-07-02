#include <QtGui/QApplication>
#include "mainwidget.h"
#include <QTextCodec>

#include "titlewidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

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
