#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>

namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit UserWidget(QWidget *parent = 0);
    ~UserWidget();
protected:
    void showEvent(QShowEvent *);
private slots:
    void on_pushButton_clicked();

private:
    Ui::UserWidget *ui;
};

inline UserWidget *userWidget()
{
    static UserWidget *w = NULL;
    if(w == NULL)
    {
        w = new UserWidget();
    }
    return w;
}


#endif // USERWIDGET_H
