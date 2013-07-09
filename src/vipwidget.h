#ifndef VIPWIDGET_H
#define VIPWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
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

    void on_pushButton_OpenCard_clicked();

private:
    Ui::VipWidget *ui;
    QSqlTableModel *m_TableModel;
    QSqlQueryModel *m_QueryModel;
    bool selectVipInfoByCardID(const QString id);
    bool writeInfoToCard();
};

#endif // VIPWIDGET_H
