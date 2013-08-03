#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include "adddiningtablewidget.h"
#include "dishescountwidget.h"
namespace Ui {
class TableWidget;
}

class TableWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TableWidget(QWidget *parent = 0);
    ~TableWidget();
    void updateView();
protected:
    void resizeEvent(QResizeEvent *);
    void showEvent(QShowEvent *);
private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_toolButton_clicked();
    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_add_clicked();

    void on_toolButton_delete_clicked();

    void on_listView_customContextMenuRequested(const QPoint &pos);

    void combineTable();
    void splitTable();

private:
    void showDishesInfo(const QString &orderId);
    void enableFunction(bool state);
    void clearDishesList();
private:
    Ui::TableWidget *ui;
    QSqlQueryModel *m_tableModel;
    AddDiningTableWidget m_addWidget;
    DishesCountWidget m_countWidget;

};

inline TableWidget *tableWidget()
{
    static TableWidget *w = NULL;
    if(w == NULL)
    {
        w = new TableWidget();
    }
    return w;
}


#endif // TABLEWIDGET_H
