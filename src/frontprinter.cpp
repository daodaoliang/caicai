#include "frontprinter.h"
#include <QTextCodec>
#include <QCoreApplication>
#include <QDateTime>
#include <QByteArray>
#include <QVariant>
#include <QDebug>
QString gb2312ToUtf8(const char *szString, int nSize)
{
    if(nSize == -1)
    {
        return QTextCodec::codecForName("GB2312")->toUnicode(szString);
    }
    else
    {
        return QTextCodec::codecForName("GB2312")->toUnicode(szString, nSize);
    }
}

frontprinter::frontprinter(QObject *parent) :
    QObject(parent)
{
    QFont font = m_Doc.defaultFont();
    m_Doc.setTextWidth(1);
    //font.setBold(true);
    font.setPointSize(2);
    font.setPixelSize(2);
    font.setLetterSpacing(QFont::AbsoluteSpacing,0.1);
    m_Doc.setDefaultFont(font);
    QSizeF s = QSizeF(m_Printer.logicalDpiX()/2,m_Printer.logicalDpiY()*25);
    m_Doc.setPageSize(s);
    m_Printer.setOutputFormat(QPrinter::NativeFormat);
    qDebug()<<"zi ti"<<font.family();
}

bool frontprinter::print(const QString &tableId, const QList<DishesInfo> &dishes, const QString &orderId, double paid)
{
    QString cmd = "";
    cmd.append(tr("旗鼓村米线 ")+qApp->property("name").toString()+"<br>");
    cmd.append(tr("订单号: ")+ orderId+"<br>");
    cmd.append(tr("订单类型: %1").arg(dishes.first().type ? "退菜": "点菜")+"<br>");
    cmd.append(tr("时间: ")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"<br>");
    cmd.append(tr("桌号: ")+tableId+"<br>");
    double money1 = 0;
    double price = 0;
    QString bz = "";
    int cout = 0;
    foreach(DishesInfo dish, dishes)
    {
        money1 += dish.price * dish.count;
    }
    double rest1 = money1 - paid;
    int num = rest1 / 6;
    qDebug()<<"pay"<<money1<<paid;
    foreach(DishesInfo dish, dishes)
    {
        qDebug()<<dish.name<<dish.count << dish.dishType <<orderHelperInstance()->isDiscount(dish.name);
        price = dish.price;
        bz = "";
        if(dish.dishType == 1 && orderHelperInstance()->isDiscount(dish.name) && cout < num)
        {
            qDebug()<<"taocan---------------------------------------------------";
            if(dish.count <= num - cout)
            {
                price = price -6;
                bz = tr("(套餐)");
                cout = cout+dish.count;
                cmd.append(dish.name+ QString::number(dish.count)+tr("份 单价%1元 %2").arg(price, 0, 'f', 2).arg(bz)+"<br>");
            }else
            {
                int ord = dish.count - (num - cout);
                bz = tr("(套餐)");
                cmd.append(dish.name+ QString::number(num-cout)+tr("份 单价%1元 %2").arg(price-6, 0, 'f', 2).arg(bz)+"<br>");
                bz = "";
                cmd.append(dish.name+ QString::number(ord)+tr("份 单价%1元 %2").arg(price, 0, 'f', 2).arg(bz)+"<br>");
                cout = num;
            }
        }else
        {
            cmd.append(dish.name+ QString::number(dish.count)+tr("份 单价%1元 %2").arg(price, 0, 'f', 2).arg(bz)+"<br>");
        }
        money1 += dish.price * dish.count;
    }
    //打印优惠金额
    QString restString1 = "优惠: " + QString::number(rest1, 'f', 2) + "元";
    cmd.append(restString1+"<br>");
    cmd.append("金额: " + QString::number(paid, 'f', 2) + "元"+"<br>");
    cmd.append("谢谢惠顾！  已找零！<br>");
    //cmd.append("已找零！<br>");
    //打印

    m_Doc.setHtml("<html>"+gb2312ToUtf8(cmd.toLocal8Bit().data())+"</html>");
    qDebug()<<"print:"<<gb2312ToUtf8(cmd.toLocal8Bit().data());
    m_Doc.print(&m_Printer);
    m_Printer.newPage();
    return true;
}

QByteArray frontprinter::createLine(const QString &text)
{
    QByteArray line;
    char tmp[36];
    memset(tmp, 0, 36);
    strncpy(tmp, text.toLocal8Bit().data(), 36);
    line.append(tmp, 36);
    line.append(0x0a);
    line.append("<br>");
    return line;
}

QByteArray frontprinter::createDishes(const DishesInfo &dishes)
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
    //line.append(0x0a);
    return line;
}

QByteArray frontprinter::createSplit()
{
    QByteArray line;
    char tmp[36];
    memset(tmp, '-', 36);
    line.append(tmp, 36);
    return line;
}
