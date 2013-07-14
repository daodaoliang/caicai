#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include "sqlmanager.h"
#include <QItemDelegate>
#include <QVector>
#include <QTableView>
class MyTableModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    MyTableModel(QWidget *obj = NULL);
    QVariant data(const QModelIndex &item, int role) const;
};

namespace Ui {
class DetailWidget;
}

class DetailWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DetailWidget(QWidget *parent = 0);
    ~DetailWidget();
    void showDetail(const QString &sql);
private:
    Ui::DetailWidget *ui;
    MyTableModel m_model;
};

#endif // DETAILWIDGET_H
