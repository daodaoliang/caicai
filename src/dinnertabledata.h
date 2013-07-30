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
    //��̨
    bool openTable(const QString &tableId, const QString &orderId, int peopleCount);
    //��̨
    bool combineTable(const QStringList &tableList, const QString &orderId);
    //��̨
    bool closeTable(const QString &tableId);
    //��̨
    bool changeTable(const QString &sourceTableId, const QString &destTableId);
    //��ȡ������
    QString getOrderByTableId(const QString &tableId);
    //��ȡ����״̬
    int getOrderState(const QString &tableId);
};

inline DinnerTableData *dinnerTableDataInstance()
{
    static DinnerTableData data;
    return &data;
}

#endif // DINNERTABLEDATA_H
