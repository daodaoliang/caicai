#include "statiswidget.h"
#include "ui_statiswidget.h"
#include "sqlmanager.h"
#include <QDebug>
StatisWidget::StatisWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisWidget)
{
    ui->setupUi(this);
    m_QueryModel = new QSqlQueryModel(this);
    m_TableModel = new QSqlTableModel(this,*getSqlManager()->getdb());
    ui->tableView->setModel(m_TableModel);
    m_TableModel->select();
    m_TableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

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
    ui->but_ToExcel->setEnabled(false);
    ui->dateTimeEdit_Start->setDate(QDate::currentDate());
    ui->dateTimeEdit_End->setDate(QDate::currentDate().addDays(1));
}

StatisWidget::~StatisWidget()
{
    delete ui;
}

void StatisWidget::on_but_Search_clicked()
{
    QString sql = "";
    m_TableModel->clear();
    if(ui->dateTimeEdit_Start->dateTime().toTime_t() > ui->dateTimeEdit_End->dateTime().toTime_t())
    {
        return;
    }
    //��������
    if(ui->box_SearchKind->currentIndex() == 0)
    {
        sql = tr("select dishes.dishesname, SUM(if(orderdetail.dishestype=0,orderdetail.dishescount,0)) as total, dishes.price from orderdetail " \
                 "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid where orderdetail.handletime between '%1' and '%2'" \
                 "group by dishes.dishesname, dishes.price " \
                 "order by total desc").arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("����"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("��������"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("����"));

    }
    //���Ա��˻���
    if(ui->box_SearchKind->currentIndex() == 1 )
    {
        //        sql = tr("select dishes.dishesname, sum(orderdetail.dishescount) ,dishes.price from orderdetail "\
        //                 "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
        //                 "where orderid in (select orderid from orderinfo where userid = %1) and dishestype = 0 and orderdetail.handletime between '%2' and '%3'"\
        //                 "group by dishes.dishesname, dishes.price")
        //                .arg(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt())
        //                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
        //                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        sql = tr("select dishes.dishesname,sum(orderdetail.dishescount),dishes.price from orderdetail "\
                 "left join dishes on dishes.dishesid = orderdetail.dishesid "\
                 "where operatorid = '%1' and dishestype = 0 and orderdetail.handletime between '%2' and '%3' "\
                 "group by dishes.dishesname,dishes.price")
                .arg(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt())
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        m_TableModel->clear();
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0, Qt::Horizontal, "��Ʒ����");
        m_TableModel->setHeaderData(1, Qt::Horizontal, "�������");
        m_TableModel->setHeaderData(2, Qt::Horizontal, "��Ʒ����");
    }
    //�˲�
    if(ui->box_SearchKind->currentIndex() == 2)
    {
        QString type = "";
        if(ui->comboBox->currentText() == "ȫ��")
        {
            type = "1=1";
        }
        else
        {
            type = tr("operatorid = '%1'").arg(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());
        }
        sql = tr("SELECT orderid,dishes.dishesname,dishes.price,dishescount,handletime from orderdetail "\
                 "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                 "where dishestype = 1 and '%1' and orderdetail.handletime between '%2' and '%3'"\
                 "GROUP BY handletime")
                .arg(type)
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0, Qt::Horizontal, "������");
        m_TableModel->setHeaderData(1, Qt::Horizontal, "����");
        m_TableModel->setHeaderData(2, Qt::Horizontal, "����");
        m_TableModel->setHeaderData(3, Qt::Horizontal, "����");
        m_TableModel->setHeaderData(4, Qt::Horizontal, "ʱ��");

    }
    //�ײ�
    if(ui->box_SearchKind->currentIndex() == 3)
    {
        QString type = "";
        if(ui->comboBox->currentText() == "ȫ��")
        {
            type = "1=1";
        }
        else
        {
            type = tr("operatorid = '%1'").arg(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());
        }
        sql = tr("select dishes.dishesname, sum(orderdetail.dishescount) ,dishes.price from orderdetail "\
                 "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                 "where '%1' and dishestype = 0 "\
                 "and dishes.dishesname like '%�ײ�%' and orderdetail.handletime between '%2' and '%3' "\
                 "group by dishes.dishesname, dishes.price")
                .arg(type)
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0, Qt::Horizontal, "�ײ�����");
        m_TableModel->setHeaderData(1, Qt::Horizontal, "����");
        m_TableModel->setHeaderData(2, Qt::Horizontal, "����");
        qDebug()<<tr("�ײ�")<<sql;
    }
    //��Ա����
    if(ui->box_SearchKind->currentIndex() == 4)
    {
        QString type = "";
        if(ui->comboBox->currentText() == "ȫ��")
        {
            type = "1=1";
        }
        else
        {
            type = tr("operatorid = '%1'").arg(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());
        }
        if(!ui->line_Vip->text().isEmpty())
        {
            sql = tr("SELECT cardid,orderid, SUM(orderdetail.dishescount * dishes.price)  as price , operatorid,handletime from orderdetail "\
                     "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                     "where paytype = 1 and cardid = '%1' and orderdetail.handletime between '%2' and '%3' and '%4'"\
                     "GROUP BY handletime")
                    .arg(ui->line_Vip->text())
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(type);
        }
        else
        {
            sql = tr("SELECT cardid,orderid, SUM(orderdetail.dishescount * dishes.price)  as price ,operatorid, handletime from orderdetail "\
                     "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                     "where paytype = 1 and orderdetail.handletime between '%1' and '%2' and '%3'"\
                     "GROUP BY handletime")
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(type);
        }
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0, Qt::Horizontal, "��Ա����");
        m_TableModel->setHeaderData(1, Qt::Horizontal, "������");
        m_TableModel->setHeaderData(2, Qt::Horizontal, "�������");
        m_TableModel->setHeaderData(3, Qt::Horizontal, "����Ա");
        m_TableModel->setHeaderData(4, Qt::Horizontal, "ʱ��");

    }
    ui->but_ToExcel->setEnabled(true);
}

void StatisWidget::on_but_ToExcel_clicked()
{
    m_excelInstance.Open(QApplication::applicationDirPath()+"/"+QDateTime::currentDateTime().date().toString("yyyyMMdd")+".xls");
    m_excelInstance.SaveDataFrTable(ui->tableView);
    m_excelInstance.Close();
    ui->but_ToExcel->setEnabled(false);
}
