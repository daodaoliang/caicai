#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
#include "toolbutton.h"

class toolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit toolWidget(QWidget *parent = 0);
    
signals:
    
public slots:
public:
    void connectToWidget(QObject *receiver);
private:
    QList<toolButton *> m_buttonList;
};

#endif // TOOLWIDGET_H
