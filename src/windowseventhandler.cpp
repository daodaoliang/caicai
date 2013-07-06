#include "windowseventhandler.h"
#include <QProcess>
#include <QApplication>
#include <windows.h>
#include <QDebug>
WindowsEventHandler::WindowsEventHandler(QWidget *parent) :
    QWidget(parent), m_wx(NULL), m_wxHandle(0)
{
    startWx();
}

WindowsEventHandler::~WindowsEventHandler()
{
    m_wx->close();
}

void WindowsEventHandler::startWx()
{
    QStringList arguList;
    arguList.append(QString::number((quint32)this->winId()));
    m_wx = new QProcess(this);
    m_wx->start(qApp->applicationDirPath() + "/WX.EXE", arguList);
}

bool WindowsEventHandler::winEvent(MSG *message, long *result)
{
    if(message->message == MESSAGETYPE)
    {
        if(m_wxHandle == 0)
        {
            m_wxHandle = message->lParam;
        }
        else
        {
            int command = message->lParam;
            if(command >= 1 && command <= 8)
            {
                QString cmd;
                QStringList cmdDetail;
                if(getRequest(&cmd, &cmdDetail, command))
                {

                }
            }
        }
    }
}

bool WindowsEventHandler::getRequest(QString *cmd, QStringList *cmdDetail, int index)
{
}
