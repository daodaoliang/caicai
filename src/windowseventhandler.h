#ifndef WINDOWSEVENTHANDLER_H
#define WINDOWSEVENTHANDLER_H

#include <QWidget>
#include <QProcess>
#include <QMap>
#include "icommandhandler.h"
class WindowsEventHandler : public QWidget
{
    Q_OBJECT
public:
    explicit WindowsEventHandler(QWidget *parent = 0);
    virtual ~WindowsEventHandler();
    enum
    {
        MESSAGETYPE = 0x0500
    };
signals:
    
public slots:
public:
protected:
    bool winEvent(MSG *message, long *result);
private:
    bool getRequest(QString *cmd, QStringList *cmdDetail, int index);
    void addCommand(ICommandHandler *command);
    void handleCommand(const QString &cmd, const QStringList &cmdDetail, int index);
    void createCommand();
private:
    void startWx();
    QProcess *m_wx;
    int m_wxHandle;
    QMap<QString, ICommandHandler *> m_commandMap;
};

#endif // WINDOWSEVENTHANDLER_H
