#ifndef DISHESCOUNTWIDGET_H
#define DISHESCOUNTWIDGET_H

#include <QDialog>

namespace Ui {
class DishesCountWidget;
}

class DishesCountWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit DishesCountWidget(QWidget *parent = 0);
    ~DishesCountWidget();
    int getDishesCount()
    {
        return m_count;
    }

protected:
    void showEvent(QShowEvent *event);
private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_8_clicked();

    void on_toolButton_9_clicked();

    void on_toolButton_7_clicked();

    void on_toolButton_12_clicked();

    void on_toolButton_11_clicked();

    void on_toolButton_10_clicked();

private:
    Ui::DishesCountWidget *ui;
    int m_count;
};

#endif // DISHESCOUNTWIDGET_H
