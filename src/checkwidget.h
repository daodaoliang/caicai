#ifndef CHECKWIDGET_H
#define CHECKWIDGET_H

#include <QWidget>
#include <QCalendarWidget>
#include <QDate>
#include <QSqlQueryModel>
#include "detailwidget.h"

namespace Ui {
class CheckWidget;
}

class CheckWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CheckWidget(QWidget *parent = 0);
    ~CheckWidget();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void getDate(const QDate &date);
    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    void loadMember();
    void setTableHeader();
    void calcTotal();
private:
    Ui::CheckWidget *ui;
    QCalendarWidget m_calendar;
    QSqlQueryModel m_model;
    DetailWidget m_detail;
};
inline CheckWidget *checkWidget()
{
    static CheckWidget *w = NULL;
    if(w == NULL)
    {
        w = new CheckWidget();
    }
    return w;
}
#endif // CHECKWIDGET_H