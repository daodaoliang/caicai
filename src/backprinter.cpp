#include "backprinter.h"
#include "configerfileprocesser.h"
#include <QCoreApplication>
#include <QDateTime>
BackPrinter::BackPrinter(QObject *parent) :
    QObject(parent)
{
}

bool BackPrinter::print(const QString &tableId, const QList<DishesInfo> &dishes, const QString &orderId, double paid)
{
    QList<DishesInfo> mixian;
    QList<DishesInfo> drink;
    //获取米线
    foreach(DishesInfo dish, dishes)
    {
        if(dish.dishType == 3)
        {
            mixian.append(dish);
        }
    }
    printDishes(tableId, mixian, orderId, paid);
    //获取非饮料
    foreach(DishesInfo dish, dishes)
    {
        if(dish.dishType != 3)
        {
            drink.append(dish);
        }
    }
    printDishes(tableId, drink, orderId, paid);
    return true;
}

bool BackPrinter::printDishes(const QString &tableId, const QList<DishesInfo> &dishes, const QString &orderId, double paid)
{
    if(dishes.isEmpty())
    {
        return true;
    }
    //连接打印机
    m_socket.connectToHost(getConfigerFileInstance()->printerIp(),
                           getConfigerFileInstance()->writerPort().toUInt());
    if(!m_socket.waitForConnected(1000))
    {
        return false;
    }
    QByteArray command;
    //打印订单号
    //    command.append("\x1c\x57\x00");
    //    command.append("\x1d\x21\x00");
    command.append(createLine(tr("订单号:")));
    command.append(createLine(orderId));
    //订单类型
    QString orderType = tr("订单类型：%1").arg(dishes.first().type ? "退菜": "点菜");
    command.append(createLine(orderType));
    //打印时间
    command.append(createLine(tr("订单时间:")));
    command.append(createLine(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));

    //    m_socket.write(command);
    //    bool ret1 = m_socket.waitForBytesWritten(2000);

    //打印桌号-----------------------字体大小不同
    //command.clear();
    QString tableIdString = tr("订单桌号:") + tableId;
    command.append(createLine(tableIdString));
    //打印分割线
    createSplit();
    //打印菜品
    double money = 0;
    foreach(DishesInfo dish, dishes)
    {
        command.append(createDishes(dish));
        money += dish.price * dish.count;
    }
    //command.append("\x1c\x57\x00");
    command.append("\x1d\x21\x11");
    //切纸
    command.append(0x1d);
    command.append(0x56);
    command.append(66);
    command.append(10);
    m_socket.write(command);
    bool ret2 = false;
    ret2 = m_socket.waitForBytesWritten(1000);
    return ret2;
}

QByteArray BackPrinter::createLine(const QString &text)
{
    QByteArray line;
    char tmp[36];
    memset(tmp, 0, 36);
    strncpy(tmp, text.toLocal8Bit().data(), 36);
    line.append(tmp, 36);
    line.append(0x0a);
    return line;
}

QByteArray BackPrinter::createDishes(const DishesInfo &dishes)
{
    QByteArray line;
    char tmp[36];
    memset(tmp, 0, 36);
    strncpy(tmp, dishes.name.toLocal8Bit().data(), 16);
    QString countString = tr("%1份").arg(QString::number(dishes.count));
    strncpy(tmp + 18, countString.toLocal8Bit().data(), 6);
    //后台打印不显示菜品价格
    //    QString priceString = tr("%1元").arg(dishes.price, 0, 'f', 2);
    //    strncpy(tmp + 26, priceString.toLocal8Bit().data(), 10);
    line.append(tmp, 26);
    line.append(0x0a);
    return line;
}

QByteArray BackPrinter::createSplit()
{
    QByteArray line;
    char tmp[36];
    memset(tmp, '-', 36);
    line.append(tmp, 36);
    return line;
}
