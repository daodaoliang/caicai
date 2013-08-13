#include "statiswidget.h"
#include "ui_statiswidget.h"
#include "sqlmanager.h"
#include <QDebug>
#include "loginwidget.h"
#include <QMessageBox>
#include "functionwidget.h"
#include "logmsg.h"
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
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->comboBox->insertItem(ui->comboBox->count(),"ȫ��",0);
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

void StatisWidget::showEvent(QShowEvent *)
{
    LoginWidget w(this);
    w.setAuthType(LoginWidget::ShowReport);
    if(!w.exec())
    {
        QMessageBox::information(this, "��ʾ", "��֤ʧ��");
        functionWidget()->changePage(0);
    }
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
        sql = tr("select tmp.dishesname,tmp.total,tmp.price from (select dishes.dishesname,orderdetail.handletime, SUM(if(orderdetail.dishestype=0,orderdetail.dishescount,-1*orderdetail.dishescount)) as total, dishes.price from orderdetail " \
                 "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid and orderdetail.handletime between '%1' and '%2'" \
                 "group by dishes.dishesname, dishes.price " \
                 "order by total desc) as tmp where total != 0 and tmp.handletime between '%1' and '%2'").arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        qDebug()<<"����"<<sql;
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
        QString type = "";
        if(ui->comboBox->currentText() == "ȫ��")
        {
            type = "1=1";
        }
        else
        {
            type = tr("operatorid = '%1'").arg(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());
        }
        sql = tr("select dishes.dishesname,sum(orderdetail.dishescount),dishes.price,userinfo.nickname from orderdetail "\
                 "left join dishes on dishes.dishesid = orderdetail.dishesid left join userinfo on orderdetail.operatorid = userinfo.userid "\
                 "where %1 and dishestype = 0 and orderdetail.handletime between '%2' and '%3' "\
                 "group by dishes.dishesname,dishes.price,orderdetail.operatorid")
                .arg(type)
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        qDebug()<<"���Ա���"<<sql;
        m_TableModel->clear();
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());

        m_TableModel->setHeaderData(0, Qt::Horizontal, "��Ʒ����");
        m_TableModel->setHeaderData(1, Qt::Horizontal, "�������");
        m_TableModel->setHeaderData(2, Qt::Horizontal, "��Ʒ����");
        m_TableModel->setHeaderData(3, Qt::Horizontal, "���Ա");
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
        sql = tr("SELECT orderid,dishes.dishesname,dishes.price,dishescount,handletime,userinfo.nickname from orderdetail "\
                 "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid left join userinfo on orderdetail.operatorid = userinfo.userid "\
                 "where dishestype = 1 and %1 and orderdetail.handletime between '%2' and '%3'"\
                 "GROUP BY handletime,orderdetail.operatorid")
                .arg(type)
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        qDebug()<<"�˲�"<<sql;
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0, Qt::Horizontal, "������");
        m_TableModel->setHeaderData(1, Qt::Horizontal, "����");
        m_TableModel->setHeaderData(2, Qt::Horizontal, "����");
        m_TableModel->setHeaderData(3, Qt::Horizontal, "����");
        m_TableModel->setHeaderData(4, Qt::Horizontal, "ʱ��");
        m_TableModel->setHeaderData(5, Qt::Horizontal, "����Ա");
    }
    //�ײ�
    if(ui->box_SearchKind->currentIndex() == 3)
    {
        QString type = "";
        if(ui->comboBox->currentText() == "ȫ��")
        {
            sql = tr("select dishes.dishesname, sum(orderdetail.dishescount) ,dishes.price from orderdetail "\
                     "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                     "where dishestype = 0 "\
                     "and dishes.dishesname like '%�ײ�%' and orderdetail.handletime between '%2' and '%3' "\
                     "group by dishes.dishesname, dishes.price")
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
            ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
            m_TableModel->setHeaderData(0, Qt::Horizontal, "�ײ�����");
            m_TableModel->setHeaderData(1, Qt::Horizontal, "����");
            m_TableModel->setHeaderData(2, Qt::Horizontal, "����");
            qDebug()<<tr("�ײ�")<<sql;
        }
        else
        {
            type = tr("operatorid = '%1'").arg(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());
            sql = tr("select dishes.dishesname, sum(orderdetail.dishescount) ,dishes.price,userinfo.nickname from orderdetail "\
                     "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid left join userinfo on orderdetail.operatorid = userinfo.userid "\
                     "where %1 and dishestype = 0 "\
                     "and dishes.dishesname like '%�ײ�%' and orderdetail.handletime between '%2' and '%3' "\
                     "group by dishes.dishesname, dishes.price,orderdetail.operatorid")
                    .arg(type)
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
            qDebug()<<tr("�ײ�")<<sql;
            ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
            m_TableModel->setHeaderData(0, Qt::Horizontal, "�ײ�����");
            m_TableModel->setHeaderData(1, Qt::Horizontal, "����");
            m_TableModel->setHeaderData(2, Qt::Horizontal, "����");
            m_TableModel->setHeaderData(3, Qt::Horizontal, "����Ա");
        }
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
            sql = tr("SELECT orderid,cardid, SUM(orderdetail.dishescount * dishes.price)  as price , operatorid,handletime from orderdetail "\
                     "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                     "where paytype = 1 and cardid = '%1' and orderdetail.handletime between '%2' and '%3' and %4 "\
                     "GROUP BY handletime")
                    .arg(ui->line_Vip->text())
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(type);
        }
        else
        {
            sql = tr("SELECT orderid,cardid,SUM(orderdetail.dishescount * dishes.price)  as price ,operatorid, handletime from orderdetail "\
                     "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                     "where paytype = 1 and orderdetail.handletime between '%1' and '%2' and %3 "\
                     "GROUP BY handletime")
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(type);
        }
        qDebug()<<"��Ա"<<sql;
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0, Qt::Horizontal, "������");
        m_TableModel->setHeaderData(1, Qt::Horizontal, "��Ա����");
        m_TableModel->setHeaderData(2, Qt::Horizontal, "�������");
        m_TableModel->setHeaderData(3, Qt::Horizontal, "����Ա");
        m_TableModel->setHeaderData(4, Qt::Horizontal, "ʱ��");

    }
    getLogMsg()->iLogMsg(sql);
    ui->but_ToExcel->setEnabled(true);
}

void StatisWidget::on_but_ToExcel_clicked()
{
    m_excelInstance.Open(QApplication::applicationDirPath()+"/"+QDateTime::currentDateTime().date().toString("yyyyMMdd")+".xls");
    m_excelInstance.SaveDataFrTable(ui->tableView);
    m_excelInstance.Close();
    ui->but_ToExcel->setEnabled(false);
}

void StatisWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug()<<"˫��"<<ui->box_SearchKind->currentText();
    if(ui->box_SearchKind->currentText() != "�˲˲�ѯ" && ui->box_SearchKind->currentText() != "��Ա���Ѳ�ѯ")
    {
        return;
    }
    //QString orderId =((QSqlQueryModel*)m_TableModel)->record(index.row()).value(0).toString();
    QString orderId = ((QSqlQueryModel*)m_TableModel)->data(((QSqlQueryModel*)m_TableModel)->index(index.row(),0)).toString();
    QString sql = tr("select dishes.dishesname, orderdetail.dishescount, dishes.price, orderdetail.dishestype,orderdetail.orderid,orderdetail.handletime from orderdetail " \
                     "LEFT JOIN dishes on orderdetail.dishesid = dishes.dishesid where orderid = '%1'").arg(orderId);
    qDebug()<<"˫��"<<sql;
    m_detail.showDetail(sql);
}
