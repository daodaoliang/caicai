#ifndef DINNERWIDGET_H
#define DINNERWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include "orderhelper.h"
namespace Ui {
class DinnerWidget;
}

class DinnerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DinnerWidget(QWidget *parent = 0);
    ~DinnerWidget();
    void updateData();
public:


private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_4_clicked();

private:

    //Æô¶¯µã²Ë±¦¼àÌý³ÌÐò
    void startWx();
private:
    Ui::DinnerWidget *ui;
    QSqlQueryModel *m_model;
    QList<DishesInfo> m_dishesList;
};

inline DinnerWidget *dinnerWidget()
{
    static DinnerWidget *w = NULL;
    if(w == NULL)
    {
        w = new DinnerWidget();
    }
    return w;
}

#endif // DINNERWIDGET_H
