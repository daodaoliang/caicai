#ifndef WINDOWSEVENTHANDLER_H
#define WINDOWSEVENTHANDLER_H

#include <QWidget>
#include <QProcess>
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
private:
    void startWx();
    QProcess *m_wx;
    int m_wxHandle;

};

#endif // WINDOWSEVENTHANDLER_H
