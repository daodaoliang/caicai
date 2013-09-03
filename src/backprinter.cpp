#include "backprinter.h"
#include <QCoreApplication>
#include <QDateTime>
#include <QMessageBox>
#include "sqlmanager.h"
BackPrinter::BackPrinter(const QString &ip, QObject *parent) :
    QObject(parent)
{
    m_ip = ip;
}

bool BackPrinter::print(const QString &tableId, const QList<DishesInfo> &dishes, const QString &orderId,const int userid, double paid)
{
    QList<DishesInfo> mixian;
    QList<DishesInfo> drink;
    QString user  = "";
    QString sql = tr("select nickname from userinfo where userid = '%1'").arg(userid);
    QSqlQuery *query = getSqlManager()->ExecQuery(sql);
    if(query != NULL)
    {
        if(query->next())
        {
            user = query->value(0).toString();
        }
    }
    //获取米线
    qDebug()<<"mixian---";
    foreach(DishesInfo dish, dishes)
    {
        qDebug()<<dish.dishType;
        if(dish.dishType == 3)
        {
            mixian.append(dish);
        }
    }
    if(!printDishes(tableId, mixian, orderId,user, paid, "192.168.123.100"))
    {
        return false;
    }
    //获取非饮料
    qDebug()<<"yinliao---";
    foreach(DishesInfo dish, dishes)
    {
        if(dish.dishType != 3)
        {
            drink.append(dish);
        }
    }
    if(!printDishes(tableId, drink, orderId, user,paid, "192.168.123.101"))
    {
        return false;
    }
    return true;
}

bool BackPrinter::printDishes(const QString &tableId, const QList<DishesInfo> &dishes, const QString &orderId,const QString user, double paid, const QString &ip)
{
    qDebug()<<"print "<<dishes.isEmpty();
    if(dishes.isEmpty())
    {
        return true;
    }
    //连接打印机
    QTcpSocket m_socket;
    m_socket.connectToHost(ip,
                           getConfigerFileInstance()->writerPort().toUInt());
    if(!m_socket.waitForConnected(1000))
    {
        return false;
    }
    QByteArray command;
    command.clear();
    //打印订单号
    //设置正常字号
    command.append(29);
    command.append(33);
    command.append(QString::number(0).toInt());
    command.append(createLine("订单号："+orderId));
    //打印时间
    command.append("订单时间："+createLine(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    command.append(0x0a);
    //订单类型
    //command.append(tr("订单类型："));
    //设置加大字号
    //command.append("\x1d\x21\x11");
    QString orderType = (dishes.first().type ? "退菜": "点菜");
    //command.append(createLine(orderType));
    //设置正常字号
    command.append(29);
    command.append(33);
    command.append(QString::number(0).toInt());
    command.append(tr("订单桌号:"));
    //设置加大字号
    command.append("\x1d\x21\x11");
    command.append(createLine(tableId+" "+orderType+" "+user));
    command.append(0x0a);
    //打印分割线
    //command.append(createSplit());
    //打印菜品
    double money = 0;
    foreach(DishesInfo dish, dishes)
    {
        command.append(createDishes(dish));
        money += dish.price * dish.count;
    }
    //切纸
    command.append(0x1d);
    command.append(0x56);
    command.append(66);
    command.append(10);
    m_socket.write(command);
    bool ret2 = false;
    ret2 = m_socket.waitForBytesWritten(5000);
    //    m_socket.waitForDisconnected(1000);
    //    m_socket.abort();
    //    m_socket.close();
    return ret2;
}

QByteArray BackPrinter::createLine(const QString &text)
{
    QByteArray line;
    char tmp[36];
    memset(tmp, 0, 36);
    strncpy(tmp, text.toLocal8Bit().data(), qMin(36,text.toLocal8Bit().length()));
    line.append(tmp, 36);
    line.append(0x0a);
    return line;
}

QByteArray BackPrinter::createDishes(const DishesInfo &dishes)
{
    QByteArray line;
    char tmp[36];
    memset(tmp, ' ', 36);
    //memcpy(tmp, dishes.name.toLocal8Bit().data(), 16);
    char tmpdis[16];
    memset(tmpdis,' ',16);
    memcpy(tmpdis,dishes.name.toLocal8Bit().data(),qMin(16,dishes.name.toLocal8Bit().size()));
    memcpy(tmp,tmpdis,16);
    QString countString = tr("%1份").arg(QString::number(dishes.count));
    strncpy(tmp + 18, countString.toLocal8Bit().data(), 6);
    //后台打印不显示菜品价格
    //    QString priceString = tr("%1元").arg(dishes.price, 0, 'f', 2);
    //    strncpy(tmp + 26, priceString.toLocal8Bit().data(), 10);
    line.append(tmp, 24);
    line.append(0x0a);
    return line;
}

QByteArray BackPrinter::createSplit()
{
    QByteArray line;
    char tmp[20];
    memset(tmp, '-', 20);
    line.append(tmp, 20);
    line.append(0x0a);
    return line;
}
