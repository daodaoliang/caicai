#ifndef FRONTPRINTER_H
#define FRONTPRINTER_H

#include <QObject>
#include <QPrinter>
#include <QTextDocument>
#include "orderhelper.h"
QString gb2312ToUtf8(const char *szString, int nSize=-1);
class frontprinter : public QObject
{
    Q_OBJECT
public:
    explicit frontprinter(QObject *parent = 0);
    
signals:
    
public slots:
    bool print(const QString &tableId, const QList<DishesInfo> &dishes, const QString &orderId,const int userid, double paid);
    QByteArray createLine(const QString &text);
    QByteArray createDishes(const DishesInfo &dishes);
    QByteArray createSplit();
private:
    QPrinter m_Printer;
    QTextDocument m_Doc;
};
inline frontprinter *getFrontPrinter()
{
    static frontprinter w;
    return &w;
}
#endif // FRONTPRINTER_H
