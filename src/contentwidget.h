#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include "functionwidget.h"

class contentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit contentWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void changePage();
public:
private:
    FunctionWidget *m_function;
    
};

#endif // CONTENTWIDGET_H

/*
  主界面上的内容区域
*/
