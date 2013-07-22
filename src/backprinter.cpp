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
}

bool BackPrinter::printDishes(const QString &tableId, const QList<DishesInfo> &dishes, const QString &orderId, double paid)
{
    //连接打印机
    m_socket.connectToHost(getConfigerFileInstance()->printerIp(),
                           getConfigerFileInstance()->writerPort().toUInt());
    if(!m_socket.waitForConnected(1000))
    {
        return false;
    }
    QByteArray command;

    //打印公司抬头
    //command.append(createLine(qApp->property("name").toString()));
    //打印订单号
    QString printOrderId = "订单号:" + orderId;
    command.append(createLine(printOrderId));
    //订单类型
    QString orderType = tr("订单类型：%1").arg(dishes.first().type ? "退菜": "点菜");
    command.append(createLine(orderType));
    //打印时间
    QString time = "时间:" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    command.append(createLine(time));
    //打印桌号
    QString tableIdString = "桌号:" + tableId;
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
//    //打印分割线
//    createSplit();
//    //打印优惠金额
//    double rest = money - paid;
//    QString restString = "优惠:" + QString::number(rest, 'f', 2) + "元";
//    command.append(createLine(restString));
//    //打印总金额
//    QString paidString = "金额:" + QString::number(paid, 'f', 2) + "元";
//    command.append(createLine(paidString));
//    //打印结束语
//    command.append(createLine("谢谢惠顾！"));
    //切纸
    //    command.append(0x1d);
    //    command.append(0x56);
    //    command.append(66);
    //    command.append(10);
    m_socket.write(command);
    return m_socket.waitForBytesWritten(1000);
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
    QString priceString = tr("%1元").arg(dishes.price, 0, 'f', 2);
    strncpy(tmp + 26, priceString.toLocal8Bit().data(), 10);
    line.append(tmp, 36);
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
