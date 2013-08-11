#ifndef CARDDETAILWIDGET_H
#define CARDDETAILWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include "excelengine.h"

namespace Ui {
class CardDetailWidget;
}

class CardDetailWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CardDetailWidget(QWidget *parent = 0);
    ~CardDetailWidget();
protected:
    void showEvent(QShowEvent *);
private slots:
    void on_but_Search_clicked();

    void on_but_ToExcel_clicked();

private:
    Ui::CardDetailWidget *ui;
    QSqlTableModel *m_TableModel;
    QSqlQueryModel *m_QueryModel;
};
inline CardDetailWidget *cardDetailWidget()
{
    static CardDetailWidget *w = NULL;
    if(w == NULL)
    {
        w = new CardDetailWidget();
    }
    return w;
}
#endif // CARDDETAILWIDGET_H
