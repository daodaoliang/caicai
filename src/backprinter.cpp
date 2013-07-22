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
    //��ȡ����
    foreach(DishesInfo dish, dishes)
    {
        if(dish.dishType == 3)
        {
            mixian.append(dish);
        }
    }
    printDishes(tableId, mixian, orderId, paid);
    //��ȡ������
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
    //���Ӵ�ӡ��
    m_socket.connectToHost(getConfigerFileInstance()->printerIp(),
                           getConfigerFileInstance()->writerPort().toUInt());
    if(!m_socket.waitForConnected(1000))
    {
        return false;
    }
    QByteArray command;

    //��ӡ��˾̧ͷ
    //command.append(createLine(qApp->property("name").toString()));
    //��ӡ������
    QString printOrderId = "������:" + orderId;
    command.append(createLine(printOrderId));
    //��������
    QString orderType = tr("�������ͣ�%1").arg(dishes.first().type ? "�˲�": "���");
    command.append(createLine(orderType));
    //��ӡʱ��
    QString time = "ʱ��:" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    command.append(createLine(time));
    //��ӡ����
    QString tableIdString = "����:" + tableId;
    command.append(createLine(tableIdString));
    //��ӡ�ָ���
    createSplit();
    //��ӡ��Ʒ
    double money = 0;
    foreach(DishesInfo dish, dishes)
    {
        command.append(createDishes(dish));
        money += dish.price * dish.count;
    }
//    //��ӡ�ָ���
//    createSplit();
//    //��ӡ�Żݽ��
//    double rest = money - paid;
//    QString restString = "�Ż�:" + QString::number(rest, 'f', 2) + "Ԫ";
//    command.append(createLine(restString));
//    //��ӡ�ܽ��
//    QString paidString = "���:" + QString::number(paid, 'f', 2) + "Ԫ";
//    command.append(createLine(paidString));
//    //��ӡ������
//    command.append(createLine("лл�ݹˣ�"));
    //��ֽ
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
    QString countString = tr("%1��").arg(QString::number(dishes.count));
    strncpy(tmp + 18, countString.toLocal8Bit().data(), 6);
    QString priceString = tr("%1Ԫ").arg(dishes.price, 0, 'f', 2);
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
