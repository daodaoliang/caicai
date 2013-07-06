#include "windowseventhandler.h"
#include <QProcess>
#include <QApplication>
WindowsEventHandler::WindowsEventHandler(QWidget *parent) :
    QWidget(parent)
{
    startWx();
}

void WindowsEventHandler::startWx()
{
    QStringList arguList;
    arguList.append(QString::number((quint32)this->winId()));
    QProcess *myProcess = new QProcess(this);
    myProcess->start(qApp->applicationDirPath() + "/WX.EXE", arguList);
}

bool WindowsEventHandler::winEvent(MSG *message, long *result)
{
}
