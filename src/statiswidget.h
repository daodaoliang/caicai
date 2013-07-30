#ifndef STATISWIDGET_H
#define STATISWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
namespace Ui {
class StatisWidget;
}

class StatisWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit StatisWidget(QWidget *parent = 0);
    ~StatisWidget();
    
private slots:
    void on_but_Search_clicked();

private:
    Ui::StatisWidget *ui;
private:
    QSqlTableModel *m_TableModel;
    QSqlQueryModel *m_QueryModel;
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
