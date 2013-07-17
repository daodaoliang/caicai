#ifndef ORDERWIDGET_H
#define ORDERWIDGET_H

#include <QWidget>

namespace Ui {
class OrderWidget;
}

class OrderWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit OrderWidget(QWidget *parent = 0);
    ~OrderWidget();
    
private:
    Ui::OrderWidget *ui;
};

inline OrderWidget *orderWidget()
{
    static OrderWidget *w = NULL;
    if(w == NULL)
    {
        w = new OrderWidget();
    }
    return w;
}

#endif // ORDERWIDGET_H
