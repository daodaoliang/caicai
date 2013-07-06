#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QVector>
class TableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TableDelegate(QObject *parent = 0);
    
signals:
    
public slots:
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    QPixmap m_tableImage;
    QPixmap m_busyImage;
};

#endif // TABLEDELEGATE_H
