#ifndef STATISWIDGET_H
#define STATISWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include "excelengine.h"
#include "detailwidget.h"
namespace Ui {
class StatisWidget;
}

class StatisWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit StatisWidget(QWidget *parent = 0);
    ~StatisWidget();
protected:
    void showEvent(QShowEvent *);
private slots:
    void on_but_Search_clicked();

    void on_but_ToExcel_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::StatisWidget *ui;
private:
    QSqlTableModel *m_TableModel;
    QSqlQueryModel *m_QueryModel;
    ExcelEngine m_excelInstance;
    DetailWidget m_detail;
};
inline StatisWidget *statisWidget()
{
    static StatisWidget*w = NULL;
    if(w == NULL)
    {
        w = new StatisWidget();
    }
    return w;
}
#endif // STATISWIDGET_H
