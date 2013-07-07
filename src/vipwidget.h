#ifndef VIPWIDGET_H
#define VIPWIDGET_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class VipWidget;
}

class VipWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit VipWidget(QWidget *parent = 0);
    ~VipWidget();
    
private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_Save_clicked();

private:
    Ui::VipWidget *ui;
    QSqlTableModel *m_model;
};

#endif // VIPWIDGET_H
