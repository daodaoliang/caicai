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
    bool combineTable(const QString &sourceTableId, const QString &destTableId);
    //撤台
    bool closeTable(const QString &tableId);
    //拆台
    bool splitTable(const QString &tableId);
    //换台
    bool changeTable(const QString &sourceTableId, const QString &destTableId);
    //获取订单号
    QString getOrderByTableId(const QString &tableId);
    //获取餐桌状态
    int getOrderState(const QString &tableId);
    //获取新ID
    QString getNewId();
    //桌子的状态是否为正常
    int tableType(const QString &tableId);
    //删除桌子
    bool deleteTable(const QString &tableId);
    //还原桌子
    bool restoreTable(const QString &tableId);
};

inline DinnerTableData *dinnerTableDataInstance()
{
    static DinnerTableData data;
    return &data;
}

#endif // DINNERTABLEDATA_H
