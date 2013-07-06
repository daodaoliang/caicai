#include "windowseventhandler.h"
#include <QProcess>
#include <QApplication>
#include <windows.h>
#include <QDebug>
#include <QFile>
WindowsEventHandler::WindowsEventHandler(QWidget *parent) :
    QWidget(parent), m_wx(NULL), m_wxHandle(0)
{
    startWx();
}

WindowsEventHandler::~WindowsEventHandler()
{
    m_wx->close();
    addCommand(new LoginHandler());
    addCommand(new OpenMachineHandler());
    addCommand(new OpenTableHandler);
    addCommand(new ChangeTableHandler);
    addCommand(new OrderHandler);
    addCommand(new MessageHandler);
    addCommand(new BackDishHandler);
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
    QString fileName = qApp->applicationDirPath() + tr("/TXT/T%1.txt").arg(index);
    if(!QFile::exists(fileName))
    {
        return false;
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return false;
        }
        else
        {
            QString data = file.readAll();
            *cmdDetail = data.split("\n", QString::SkipEmptyParts);
            if(cmdDetail->count() == 0)
            {
                return false;
            }
            *cmd = cmdDetail->at(0);
            return true;
        }
    }
}

void WindowsEventHandler::addCommand(ICommandHandler *command)
{
    m_commandMap[command->handlerName()] = command;
}

void WindowsEventHandler::handleCommand(const QString &cmd, const QStringList &cmdDetail)
{
    ICommandHandler *handler = m_commandMap.value(cmd, NULL);
    if(handler != NULL)
    {
        handler->handleCommand(cmdDetail);
    }
}
