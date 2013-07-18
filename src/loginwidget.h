#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QDialog>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H
