#ifndef DINNERWIDGET_H
#define DINNERWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include "orderhelper.h"
#include "dishescountwidget.h"
#include "detailwidget.h"
#include "adddiningtablewidget.h"

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
    void on_listView_doubleClicked(const QModelIndex &index);

    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

private:
    //������˱���������
    void startWx();
private:
    Ui::DinnerWidget *ui;
    QSqlQueryModel *m_tableModel;
    QSqlQueryModel *m_dishesTypeModel;
    QSqlQueryModel *m_dishesModel;
    QList<DishesInfo> m_dishesList;
    DetailWidget m_detailWidget;
    AddDiningTableWidget m_addWidget;
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
