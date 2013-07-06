#ifndef WINDOWSEVENTHANDLER_H
#define WINDOWSEVENTHANDLER_H

#include <QWidget>

class WindowsEventHandler : public QWidget
{
    Q_OBJECT
public:
    explicit WindowsEventHandler(QWidget *parent = 0);
    
signals:
    
public slots:
public:
protected:
    bool winEvent(MSG *message, long *result);
private:
    void startWx();

};

#endif // WINDOWSEVENTHANDLER_H
