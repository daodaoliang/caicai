#ifndef FUNCTIONWIDGET_H
#define FUNCTIONWIDGET_H

#include <QWidget>

namespace Ui {
class FunctionWidget;
}

class FunctionWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FunctionWidget(QWidget *parent = 0);
    ~FunctionWidget();
    
private:
    Ui::FunctionWidget *ui;
};

#endif // FUNCTIONWIDGET_H
