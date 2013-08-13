#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include "sqlmanager.h"
#include <QItemDelegate>
#include <QVector>
#include <QTableView>
#include <QtGui>
#include <QMap>
class MyTableModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    MyTableModel(QWidget *obj = NULL);
    QVariant data(const QModelIndex &item, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    int colNumberWithCheckBox;
    QMap<int, Qt::CheckState> rowCheckStateMap;
    int totalColumn;
public:
signals:

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

protected:
private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::DetailWidget *ui;
    MyTableModel m_model;
    QString m_CurOrderid;
    QString m_CurOrderTime;
    double m_CurMoney;
};

#endif // DETAILWIDGET_H
