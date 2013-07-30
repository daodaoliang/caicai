#ifndef FUNCTIONWIDGET_H
#define FUNCTIONWIDGET_H

#include <QWidget>
#include <windows.h>
namespace Ui {
class FunctionWidget;
}

class FunctionWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FunctionWidget(QWidget *parent = 0);
    ~FunctionWidget();
    void changePage(int index);
protected:
    bool winEvent(MSG *message, long *result);
private:
    Ui::FunctionWidget *ui;
};
inline FunctionWidget *functionWidget()
{
    static FunctionWidget *w = NULL;
    if(w == NULL)
    {
        w = new FunctionWidget();
    }
    return w;
}


#endif // FUNCTIONWIDGET_H
