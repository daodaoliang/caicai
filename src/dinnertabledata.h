#ifndef DINNERTABLEDATA_H
#define DINNERTABLEDATA_H

#include <QObject>

class DinnerTableData : public QObject
{
    Q_OBJECT
public:
    explicit DinnerTableData(QObject *parent = 0);
    
signals:
    
public slots:
    //开台
    bool openTable(const QString &tableId, const QString &orderId, int peopleCount);
    //并台
    bool combineTable(const QStringList &tableList, const QString &orderId);
    //撤台
    bool closeTable(const QString &tableId);
    //换台
    bool changeTable(const QString &sourceTableId, const QString &destTableId);
    //获取订单号
    QString getOrderByTableId(const QString &tableId);
    //获取餐桌状态
    int getOrderState(const QString &tableId);
};

inline DinnerTableData *dinnerTableDataInstance()
{
    static DinnerTableData data;
    return &data;
}

#endif // DINNERTABLEDATA_H
