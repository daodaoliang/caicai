#include "checkwidget.h"
#include "ui_checkwidget.h"
#include <QDebug>
#include "sqlmanager.h"
#include <QSqlRecord>
#include <QMessageBox>
#include "functionwidget.h"
#include "loginwidget.h"
#include "logmsg.h"
CheckWidget::CheckWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckWidget), m_calendar(this)
{
    ui->setupUi(this);
    m_calendar.hide();
    connect(&m_calendar, SIGNAL(clicked(QDate)), this, SLOT(getDate(QDate)));
    ui->lineEdit->installEventFilter(this);
    loadMember();
    //设置表头
    ui->tableView->setModel(&m_model);
    setTableHeader();
    //设置默认日期
    ui->dateTimeEdit_Start->setDate(QDate::currentDate());
    ui->dateTimeEdit_End->setDate(QDate::currentDate().addDays(1));
    ui->lineEdit_Orderid->setText(QDate::currentDate().toString("yyyyMMdd"));
    ui->lineEdit->setVisible(false);
    m_calendar.setVisible(false);
    ui->pushButton_2->setEnabled(false);

    //ui->tableView->setEditTriggers(QAbstractItemView::EditKeyPressed);

}

CheckWidget::~CheckWidget()
{
    delete ui;
}

bool CheckWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->lineEdit && event->type() == QEvent::FocusIn)
    {
        m_calendar.raise();
        m_calendar.show();
        m_calendar.move(ui->lineEdit->x(), ui->lineEdit->y()+ ui->lineEdit->height());
        m_calendar.resize(248,169);
        return true;
    }
    return false;
}

void CheckWidget::showEvent(QShowEvent *)
{
    LoginWidget w(this);
    w.setAuthType(LoginWidget::ShowReport);
    if(!w.exec())
    {
        QMessageBox::information(this, "提示", "验证失败");
        functionWidget()->changePage(0);
    }
}

void CheckWidget::getDate(const QDate &date)
{
    m_calendar.hide();
    m_Date=date.toString("yyyyMMdd");
    m_Date.append(QTime::currentTime().toString("hhmm"));
    ui->lineEdit->setText(m_Date);
}

void CheckWidget::loadMember()
{
    ui->comboBox->insertItem(ui->comboBox->count(), "全部", 0);
    //ui->comboBox->insertItem(ui->comboBox->count(),"订单号",0);
    QString sql = tr("select userid, nickname from userinfo");
    getLogMsg()->iLogMsg(sql);
    QSqlQuery *query = getSqlManager()->ExecQuery(sql);
    if(query)
    {
        while(query->next())
        {
            ui->comboBox->insertItem(ui->comboBox->count(), query->value(1).toString(), query->value(0));
        }
    }
    ui->comboBox->setCurrentIndex(0);
}

void CheckWidget::setTableHeader()
{


}

void CheckWidget::calcTotal()
{
    QString text;
    if(ui->comboBox->currentText().compare("全部") != 0)
    {
        text.append(tr("服务员：<font size='6' color='red'><b>%1    </b></font>").arg(ui->comboBox->currentText()));
    }
    //text.append(tr("日期:<font size='6' color='red'><b>%1    </b></font>    ").arg(ui->lineEdit->text()));
    text.append(tr("日期:<font size='4' color='red'>%1至%2</font>    ")
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
    double paid = 0;
    double cash = 0;
    double card = 0;

    QString sql = "";
    sql = tr("select SUM(dishescount * dishes.price * if(orderdetail.dishestype = 0,1,-1)) from orderdetail"\
             " LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid"\
             " where orderdetail.paytype = 1 and (handletime between '%1' and '%2')")
            .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    int operatorId = ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();
    if(operatorId > 0)
    {
        sql.append(tr(" and operatorId = '%1'").arg(operatorId));
    }
    if(ui->comboBox_2->currentText() == "订单号")
    {
        sql.append(tr(" and orderdetail.orderid = '%1'").arg(ui->lineEdit_Orderid->text()));
    }
    if(ui->comboBox_2->currentText() == "桌号")
    {
        sql.append(tr(" and RIGHT(orderid,4)='%1'").arg(ui->lineEdit_Orderid->text().toInt(),4, 10, QLatin1Char('0')));
    }
    qDebug() << sql;
    getLogMsg()->iLogMsg(sql);
    QSqlQuery query(sql, *getSqlManager()->getdb());
    if(query.exec())
    {
        if(query.next())
        {
            card = query.value(0).toDouble();
        }
    }
    else
    {
        return;
    }
    sql = tr("select SUM(dishescount * dishes.price * if(orderdetail.dishestype = 0,1,-1)) from orderdetail"\
             " LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid"\
             " where orderdetail.paytype = 0 and (handletime between '%1' and '%2')")
            .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(operatorId > 0)
    {
        sql.append(tr(" and operatorId = '%1'").arg(operatorId));
    }
    if(ui->comboBox_2->currentText() == "订单号")
    {
        sql.append(tr(" and orderdetail.orderid = '%1'").arg(ui->lineEdit_Orderid->text()));
    }
    if(ui->comboBox_2->currentText() == "桌号")
    {
        sql.append(tr(" and RIGHT(orderid,4)='%1'").arg(ui->lineEdit_Orderid->text().toInt(),4, 10, QLatin1Char('0')));
    }
    query.clear();
    getLogMsg()->iLogMsg(sql);
    if(query.exec(sql))
    {
        if(query.next())
        {
            cash = query.value(0).toDouble();
        }
    }
    else
    {
        return;
    }
    paid = cash + card;
    text.append(tr("总营业额:<font size='6' color='red'><b>%1</b></font>元；").arg(paid));
    text.append(tr("现金：<font size='6' color='red'><b>%1</b></font>元；").arg(cash));
    text.append(tr("会员卡金额：<font size='6' color='red'><b>%1</b></font>元").arg(card));
    ui->label_3->setText(text);
}

void CheckWidget::on_pushButton_clicked()
{
    ui->pushButton_2->setEnabled(true);
    QDate date = QDate::fromString(ui->lineEdit->text(), "yyyy-MM-dd");
    if(!date.isValid())
    {
        date = QDate::currentDate();
    }
    QDate lastDate = date.addDays(1);
    QString sql = "";
    //    if(ui->comboBox_2->currentText() != "全部")
    //    {
    //        if(ui->comboBox_2->currentText() == "订单号")
    //        {
    //            //            sql = tr("select orderid, accounts, tableid,  begintime, userinfo.nickname from orderinfo "\
    //            //                     "LEFT JOIN userinfo on userinfo.userid = orderinfo.userid "\
    //            //                     "where orderid = '%1' ").arg(ui->lineEdit_Orderid->text());
    //            sql = tr("select orderdetail.orderid, dishes.dishesname, dishes.price, orderdetail.dishescount, orderdetail.handletime,"\
    //                     "orderdetail.dishestype, orderdetail.paytype, orderdetail.cardid from orderdetail "\
    //                     "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid "\
    //                     "where (handletime between '%1' and '%2' and orderid = '%3')")
    //                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
    //                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
    //                    .arg(ui->lineEdit_Orderid->text());
    //        }
    //        if(ui->comboBox_2->currentText() == "桌号")
    //        {
    //            //            sql = tr("select orderid, accounts, tableid,  begintime, userinfo.nickname from orderinfo "\
    //            //                     "LEFT JOIN userinfo on userinfo.userid = orderinfo.userid "\
    //            //                     "where tableid = '%1' ").arg(tr("%1").arg(ui->lineEdit_Orderid->text().toInt(),4, 10, QLatin1Char('0')));
    //            sql = tr("select orderdetail.orderid, dishes.dishesname, dishes.price, orderdetail.dishescount, orderdetail.handletime,"\
    //                     "orderdetail.dishestype, orderdetail.paytype, orderdetail.cardid from orderdetail "\
    //                     "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid "\
    //                     "where (handletime between '%1' and '%2' and RIGHT(orderid,4) = '%3')")
    //                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
    //                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
    //                    .arg(ui->lineEdit_Orderid->text().toInt(),4, 10, QLatin1Char('0'));
    //        }
    //    }
    //    else
    {
        if(ui->dateTimeEdit_Start->dateTime().toTime_t() > ui->dateTimeEdit_End->dateTime().toTime_t())
        {
            return;
        }
        //    QString sql = tr("select orderid, accounts, paid, tableid,  begintime, userinfo.nickname from orderinfo "\
        //            "LEFT JOIN userinfo on userinfo.userid = orderinfo.userid "\
        //                     "where begintime > '%1' and begintime <= '%2' ").arg(date.toString("yyyy-MM-dd")).arg(lastDate.toString("yyyy-MM-dd"));
        sql = tr("select orderdetail.orderid, dishes.dishesname, dishes.price, orderdetail.dishescount, orderdetail.handletime,"\
                 "orderdetail.dishestype, orderdetail.paytype, orderdetail.cardid,operatorid from orderdetail "\
                 "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid "\
                 "where (handletime between '%1' and '%2')").arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        int userId = ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();
        if(userId > 0)
        {
            sql.append(tr(" and operatorid = %1").arg(userId));
        }
        if(ui->comboBox_2->currentText() == "订单号")
        {
            sql.append(tr(" and orderdetail.orderid = '%1'").arg(ui->lineEdit_Orderid->text()));
        }
        if(ui->comboBox_2->currentText() == "桌号")
        {
            sql.append(tr(" and RIGHT(orderid,4)='%1'").arg(ui->lineEdit_Orderid->text().toInt(),4, 10, QLatin1Char('0')));
        }
    }
    qDebug()<<"account"<<sql;
    getLogMsg()->iLogMsg(sql);
    QSqlQuery query(sql, *getSqlManager()->getdb());
    m_model.setQuery(query);
    m_model.setHeaderData(0, Qt::Horizontal, tr("订单号"));
    m_model.setHeaderData(1, Qt::Horizontal, tr("菜品名称"));
    m_model.setHeaderData(2, Qt::Horizontal, tr("单价"));
    m_model.setHeaderData(3, Qt::Horizontal, tr("数量"));
    m_model.setHeaderData(4, Qt::Horizontal, tr("下单时间"));
    m_model.setHeaderData(5, Qt::Horizontal, tr("订单类型"));
    m_model.setHeaderData(6, Qt::Horizontal, tr("支付类型"));
    m_model.setHeaderData(7, Qt::Horizontal, tr("支付卡号"));
    m_model.setHeaderData(8, Qt::Horizontal, tr("服务员"));
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(4, 200);
    calcTotal();

}

void CheckWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString orderId = m_model.record(index.row()).value(0).toString();
    QString sql = tr("select dishes.dishesname, orderdetail.dishescount, dishes.price, orderdetail.dishestype,orderdetail.orderid from orderdetail " \
                     "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid where orderid = '%1'").arg(orderId);
    getLogMsg()->iLogMsg(sql);
    m_detail.showDetail(sql);
}

void CheckWidget::on_pushButton_2_clicked()
{
    if(m_Date.isEmpty())
    {
        m_Date=QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    }
    m_excelInstance.Open(QApplication::applicationDirPath()+"/"+m_Date+".xls");
    m_excelInstance.SaveDataFrTable(ui->tableView);
    m_excelInstance.Close();
    ui->pushButton_2->setEnabled(false);
}


DetailModel::DetailModel(QWidget *obj) : QSqlQueryModel(obj)
{
}

QVariant DetailModel::data(const QModelIndex &item, int role) const
{
    QString sql = "";
    QSqlQuery *query = NULL;
    QVariant value = QSqlQueryModel::data(item, role);
    if (value.isValid() && role == Qt::DisplayRole)
    {
        if (item.column() == 2)
            return value.toString().append("元");
        else if (item.column() == 3)
            return value.toString().append("份");
        else if(item.column() == 5)
            return value.toInt() == 0 ? "点菜" : "退菜";
        else if(item.column() == 6)
            return value.toInt() == 0 ? "现金" : "会员卡";
        else if(item.column() == 8)
        {
            sql = tr("select nickname from userinfo where userid = '%1'").arg(value.toInt());
            getLogMsg()->iLogMsg(sql);
            query = getSqlManager()->ExecQuery(sql);
            if(query != NULL)
            {
                if(query->next())
                {
                    return query->value(0).toString();
                }
            }
        }
    }
    return value;
}
