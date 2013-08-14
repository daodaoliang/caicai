#ifndef MEMBERCUSTOMWIDGET_H
#define MEMBERCUSTOMWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include "detailwidget.h"
namespace Ui {
class MemberCustomWidget;
}

class MemberCustomWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MemberCustomWidget(QWidget *parent = 0);
    ~MemberCustomWidget();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MemberCustomWidget *ui;
    QSqlQueryModel m_model;
    DetailWidget m_detail;
};

inline MemberCustomWidget *memberCustomWidgetInstance()
{
    static MemberCustomWidget *w = NULL;
    if(w == NULL)
    {
        w = new MemberCustomWidget();
    }
    return w;
}

#endif // MEMBERCUSTOMWIDGET_H
