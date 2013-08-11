#ifndef VIPWIDGET_H
#define VIPWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QMultiMap>
namespace Ui {
class VipWidget;
}
const int m_Interval = 15;
class VipWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit VipWidget(QWidget *parent = 0);
    ~VipWidget();
    
private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_OpenCard_clicked();

    void on_pushButton_Cancle_clicked();

    void on_but_NextPage_clicked();

    void on_but_PreviousPage_clicked();

    void on_but_Skip_clicked();

    void slot_Sort(int column);
    void on_but_Recharge_clicked();

    void on_but_CancleCharge_clicked();

    void on_but_querenchong_clicked();

    void on_but_pay_clicked();

    void on_but_ChangeMoeny_clicked();

private:
    Ui::VipWidget *ui;
    QSqlTableModel *m_TableModel;
    QSqlQueryModel *m_QueryModel;
    int selectVipInfoByCardID(const QString id);
    bool writeInfoToCard();
    void resetText();
    void setTextEnable(bool enable);
    void updateRecord(int startPage);
    void loadComBox();
    void setPageCount();
    void resetPageInfo();
    int m_RecordCount;
    int m_PageCount;
    int m_CurPage;
    QMultiMap<QString,int> m_BoxMap;
    //
    QString m_CurCardSnr;
    //记录在保存时需要执行的sql
    QString m_Sql;
    int m_nOperid;
public:
    QString payMoney(const double &money, const QString &orderid);
    bool backMoney(const QString &cardid,const double &money,const QString &orderid);
};
inline VipWidget *vipWidget()
{
    static VipWidget *w = NULL;
    if(w == NULL)
    {
        w = new VipWidget();
    }
    return w;
}
#endif // VIPWIDGET_H
