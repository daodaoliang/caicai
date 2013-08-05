#include "checkwidget.h"
#include "ui_checkwidget.h"
#include <QDebug>
#include "sqlmanager.h"
#include <QSqlRecord>
CheckWidget::CheckWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckWidget), m_calendar(this)
{
    ui->setupUi(this);
    m_calendar.hide();
    connect(&m_calendar, SIGNAL(clicked(QDate)), this, SLOT(getDate(QDate)));
    ui->lineEdit->installEventFilter(this);
    loadMember();
    //���ñ�ͷ
    ui->tableView->setModel(&m_model);
    setTableHeader();
    //����Ĭ������
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

void CheckWidget::getDate(const QDate &date)
{
    m_calendar.hide();
    m_Date=date.toString("yyyyMMdd");
    m_Date.append(QTime::currentTime().toString("hhmm"));
    ui->lineEdit->setText(m_Date);
}

void CheckWidget::loadMember()
{
    ui->comboBox->insertItem(ui->comboBox->count(), "ȫ��", 0);
    ui->comboBox->insertItem(ui->comboBox->count(),"������",0);
    QString sql = tr("select userid, nickname from userinfo");
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
    if(ui->comboBox->currentText().compare("ȫ��") != 0)
    {
        text.append(tr("����Ա��<font size='6' color='red'><b>%1    </b></font>").arg(ui->comboBox->currentText()));
    }
    //text.append(tr("����:<font size='6' color='red'><b>%1    </b></font>    ").arg(ui->lineEdit->text()));
    text.append(tr("����:<font size='4' color='red'>%1��%2</font>    ")
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
    double paid = 0;
    double cash = 0;
    double card = 0;
    for(int i = 0; i < m_model.rowCount(); i++)
    {
        paid += m_model.record(i).value(2).toDouble();
    }
    QString sql = "";
    sql = tr("select SUM(accounts) as money from orderinfo where paytype = 1 and (begintime between '%1' and '%2')")
            .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
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
    sql = tr("select SUM(accounts) as money from orderinfo where paytype = 0 and (begintime between '%1' and '%2')")
            .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.clear();
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
    text.append(tr("��Ӫҵ��:<font size='6' color='red'><b>%1</b></font>Ԫ").arg(paid));
    text.append(tr("�ֽ�:<font size='6' color='red'><b>%1</b></font>Ԫ��").arg(cash));
    text.append(tr("��Ա�����:<font size='6' color='red'><b>%1</b></font>Ԫ").arg(card));
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
    if(ui->comboBox->currentText() == "������")
    {
        sql = tr("select orderid, accounts, paid, tableid,  begintime, userinfo.nickname from orderinfo "\
                 "LEFT JOIN userinfo on userinfo.userid = orderinfo.userid "\
                 "where orderid = '%1' ").arg(ui->lineEdit_Orderid->text());
    }
    else
    {
        if(ui->dateTimeEdit_Start->dateTime().toTime_t() > ui->dateTimeEdit_End->dateTime().toTime_t())
        {
            return;
        }
        //    QString sql = tr("select orderid, accounts, paid, tableid,  begintime, userinfo.nickname from orderinfo "\
        //            "LEFT JOIN userinfo on userinfo.userid = orderinfo.userid "\
        //                     "where begintime > '%1' and begintime <= '%2' ").arg(date.toString("yyyy-MM-dd")).arg(lastDate.toString("yyyy-MM-dd"));
        sql = tr("select orderid, accounts, paid, tableid,  begintime, userinfo.nickname from orderinfo "\
                 "LEFT JOIN userinfo on userinfo.userid = orderinfo.userid "\
                 "where begintime > '%1' and begintime <= '%2' ").arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        int userId = ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();
        if(userId > 0)
        {
            sql.append(tr(" and orderinfo.userid = %1").arg(userId));
        }
    }
    qDebug()<<"account"<<sql;
    QSqlQuery query(sql, *getSqlManager()->getdb());
    m_model.setQuery(query);
    m_model.setHeaderData(0, Qt::Horizontal, tr("������"));
    m_model.setHeaderData(1, Qt::Horizontal, tr("Ӧ��"));
    m_model.setHeaderData(2, Qt::Horizontal, tr("ʵ��"));
    m_model.setHeaderData(3, Qt::Horizontal, tr("����"));
    m_model.setHeaderData(4, Qt::Horizontal, tr("�µ�ʱ��"));
    m_model.setHeaderData(5, Qt::Horizontal, tr("����Ա"));
    calcTotal();

}

void CheckWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString orderId = m_model.record(index.row()).value(0).toString();
    QString sql = tr("select dishes.dishesname, orderdetail.dishescount, dishes.price, orderdetail.dishestype,orderdetail.orderid from orderdetail " \
                     "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid where orderid = '%1'").arg(orderId);
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
