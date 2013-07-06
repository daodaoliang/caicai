#ifndef DINNERWIDGET_H
#define DINNERWIDGET_H

#include <QWidget>

namespace Ui {
class DinnerWidget;
}

class DinnerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DinnerWidget(QWidget *parent = 0);
    ~DinnerWidget();
private:
    void startWx();
private:
    Ui::DinnerWidget *ui;
};

#endif // DINNERWIDGET_H
