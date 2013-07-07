#include "readonlydelegate.h"

readonlyDelegate::readonlyDelegate()
{
}
QWidget *readonlyDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{

    return NULL;
}
