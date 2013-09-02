#include "carddetailwidget.h"
#include "ui_carddetailwidget.h"
#include "loginwidget.h"
#include "functionwidget.h"
#include <QMessageBox>
#include <QDebug>
#include "sqlmanager.h"
CardDetailWidget::CardDetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardDetailWidget)
{
    ui->setupUi(this);
    m_QueryModel = new QSqlQueryModel(this);
    m_TableModel = new QSqlTableModel(this,*getSqlManager()->getdb());
    ui->tableView->setModel(m_TableModel);
    m_TableModel->select();
    m_TableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->box_Server->insertItem(ui->box_Server->count(),"ȫ��",0);
    QString sql = tr("select userid, nickname from userinfo");
    QSqlQuery *query = getSqlManager()->ExecQuery(sql);
    if(query)
    {
        while(query->next())
        {
            ui->box_Server->insertItem(ui->box_Server->count(), query->value(1).toString(), query->value(0));
        }
    }
    ui->box_Server->setCurrentIndex(0);
    ui->but_ToExcel->setEnabled(false);
    ui->dateTimeEdit_Start->setDate(QDate::currentDate());
    ui->dateTimeEdit_End->setDate(QDate::currentDate().addDays(1));
}

CardDetailWidget::~CardDetailWidget()
{
    delete ui;
}

void CardDetailWidget::showEvent(QShowEvent *)
{
    LoginWidget w(this);
    w.setAuthType(LoginWidget::ShowReport);
    if(!w.exec())
    {
        QMessageBox::information(this, "��ʾ", "��֤ʧ��");
        functionWidget()->changePage(0);
    }
}

void CardDetailWidget::on_but_Search_clicked()
{
    QString sql = "";
    ui->label_Info->clear();
    m_TableModel->clear();
    if(ui->box_Kind->currentText() == tr("������¼"))
    {
        sql = tr("select memcardid,member.`name`,member.membertypeid,userinfo.nickname,handletime from memcarddetail "\
                 "left join userinfo on memcarddetail.operatorid = userinfo.userid left join member on memcarddetail.memcardid = member.cardid "\
                 "where memcarddetail.handletype = 6 and handletime between ('%1') and ('%2')")
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        if(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt() != 0)
        {
            sql.append(tr(" and memcarddetail.operatorid = '%1'").arg(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt()));
        }
        if(!ui->lineEdit_Cardid->text().isEmpty())
        {
            sql.append(tr(" and memcarddetail.memcardid = '%1'").arg(ui->lineEdit_Cardid->text()));
        }
        qDebug()<<"card detail:"<<sql;
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("��������"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("�û���"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("�û�����"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("��������Ա"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("����ʱ��"));
    }
    if(ui->box_Kind->currentText() == tr("��ֵ��¼"))
    {
        sql = tr("select memcardid,member.`name`,member.membertypeid,handlemoney,moremoney,userinfo.nickname,handletime from memcarddetail "\
                 "left join userinfo on memcarddetail.operatorid = userinfo.userid left join member on memcarddetail.memcardid = member.cardid "\
                 "where memcarddetail.handletype = 1 and handletime between ('%1') and ('%2')")
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QString sql2 = tr("select sum(handlemoney) from memcarddetail "\
                          "left join userinfo on memcarddetail.operatorid = userinfo.userid "\
                          "where memcarddetail.handletype = 1 and handletime between ('%1') and ('%2')")
                         .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                         .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        if(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt() != 0)
        {
            sql.append(tr(" and memcarddetail.operatorid = '%1'").arg(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt()));
            sql2.append(tr(" and memcarddetail.operatorid = '%1'").arg(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt()));
        }
        if(!ui->lineEdit_Cardid->text().isEmpty())
        {
            sql.append(tr(" and memcarddetail.memcardid = '%1'").arg(ui->lineEdit_Cardid->text()));
            sql2.append(tr(" and memcarddetail.memcardid = '%1'").arg(ui->lineEdit_Cardid->text()));
        }
        qDebug()<<"card detail:"<<sql;
        qDebug()<<"total money:"<<sql2;
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("��ֵ����"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("�û���"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("�û�����"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("��ֵ���"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("�Żݽ��"));
        m_TableModel->setHeaderData(5,Qt::Horizontal,tr("��ֵ����Ա"));
        m_TableModel->setHeaderData(6,Qt::Horizontal,tr("��ֵʱ��"));
        m_QueryModel->setQuery(sql2,*getSqlManager()->getdb());
        QString total = "0";
        if(m_QueryModel->query().next())
        {
            total = m_QueryModel->query().value(0).toString();
        }
        QString text = (tr("����:<font size='4' color='red'>%1��%2</font>    ")
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
        QString info = ui->box_Server->currentText()+tr(" ��ֵ�ֽ���:<font size='6' color='red'><b>%1</b></font>Ԫ��")
                .arg(total);
        ui->label_Info->setText(text+info);
    }
    if(ui->box_Kind->currentText() == tr("���Ѽ�¼"))
    {
        sql = tr("select memcardid,member.`name`,member.membertypeid,handlemoney,orderid,userinfo.nickname,handletime from memcarddetail "\
                 "left join userinfo on memcarddetail.operatorid = userinfo.userid left join member on memcarddetail.memcardid = member.cardid "\
                 "where memcarddetail.handletype = 2 and handletime between ('%1') and ('%2')")
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QString sql2 = tr("select sum(handlemoney) from memcarddetail "\
                          "left join userinfo on memcarddetail.operatorid = userinfo.userid "\
                          "where memcarddetail.handletype = 2 and handletime between ('%1') and ('%2')")
                         .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                         .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        if(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt() != 0)
        {
            sql.append(tr(" and memcarddetail.operatorid = '%1'").arg(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt()));
            sql2.append(tr(" and memcarddetail.operatorid = '%1'").arg(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt()));
        }
        if(!ui->lineEdit_Cardid->text().isEmpty())
        {
            sql.append(tr(" and memcarddetail.memcardid = '%1'").arg(ui->lineEdit_Cardid->text()));
            sql2.append(tr(" and memcarddetail.memcardid = '%1'").arg(ui->lineEdit_Cardid->text()));
        }
        qDebug()<<"card detail:"<<sql;
        qDebug()<<"total money:"<<sql2;
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("���ѿ���"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("�û���"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("�û�����"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("���ѽ��"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("������"));
        m_TableModel->setHeaderData(5,Qt::Horizontal,tr("�ۿ����Ա"));
        m_TableModel->setHeaderData(6,Qt::Horizontal,tr("����ʱ��"));
        m_QueryModel->setQuery(sql2,*getSqlManager()->getdb());
        QString total = "0";
        if(m_QueryModel->query().next())
        {
            total = m_QueryModel->query().value(0).toString();
        }
        QString text = (tr("����:<font size='4' color='red'>%1��%2</font>    ")
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
        QString info = ui->box_Server->currentText()+tr(" ���ѽ��:<font size='6' color='red'><b>%1</b></font>Ԫ��")
                .arg(total);
        ui->label_Info->setText(text+info);
    }
    if(ui->box_Kind->currentText() == tr("�˿��¼"))
    {
        sql = tr("select memcardid,member.`name`,member.membertypeid,handlemoney,orderid,userinfo.nickname,handletime from memcarddetail "\
                 "left join userinfo on memcarddetail.operatorid = userinfo.userid left join member on memcarddetail.memcardid = member.cardid "\
                 "where memcarddetail.handletype = 8 and handletime between ('%1') and ('%2')")
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QString sql2 = tr("select sum(handlemoney) from memcarddetail "\
                          "left join userinfo on memcarddetail.operatorid = userinfo.userid "\
                          "where memcarddetail.handletype = 8 and handletime between ('%1') and ('%2')")
                         .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                         .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        if(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt() != 0)
        {
            sql.append(tr(" and memcarddetail.operatorid = '%1'").arg(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt()));
            sql2.append(tr(" and memcarddetail.operatorid = '%1'").arg(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt()));
        }
        if(!ui->lineEdit_Cardid->text().isEmpty())
        {
            sql.append(tr(" and memcarddetail.memcardid = '%1'").arg(ui->lineEdit_Cardid->text()));
            sql2.append(tr(" and memcarddetail.memcardid = '%1'").arg(ui->lineEdit_Cardid->text()));
        }
        qDebug()<<"card detail:"<<sql;
        qDebug()<<"total money:"<<sql2;
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("�˿��"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("�û���"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("�û�����"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("�˿���"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("�˿����"));
        m_TableModel->setHeaderData(5,Qt::Horizontal,tr("�˿����Ա"));
        m_TableModel->setHeaderData(6,Qt::Horizontal,tr("�˿�ʱ��"));
        m_QueryModel->setQuery(sql2,*getSqlManager()->getdb());
        QString total = "0";
        if(m_QueryModel->query().next())
        {
            total = m_QueryModel->query().value(0).toString();
        }
        QString text = (tr("����:<font size='4' color='red'>%1��%2</font>    ")
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
        QString info = ui->box_Server->currentText()+tr(" �˿���:<font size='6' color='red'><b>%1</b></font>Ԫ��")
                .arg(total);
        ui->label_Info->setText(text+info);
    }
    if(ui->box_Kind->currentText() == tr("��ȵ���"))
    {
        sql = tr("select memcardid,member.`name`,member.membertypeid,handlemoney,userinfo.nickname,handletime from memcarddetail "\
                 "left join userinfo on memcarddetail.operatorid = userinfo.userid left join member on memcarddetail.memcardid = member.cardid "\
                 "where memcarddetail.handletype = 3 and handletime between ('%1') and ('%2')")
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        if(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt() != 0)
        {
            sql.append(tr(" and memcarddetail.operatorid = '%1'").arg(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt()));
        }
        if(!ui->lineEdit_Cardid->text().isEmpty())
        {
            sql.append(tr(" and memcarddetail.memcardid = '%1'").arg(ui->lineEdit_Cardid->text()));
        }
        qDebug()<<"card detail:"<<sql;
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("����������"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("�û���"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("�û�����"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("��������"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("��������Ա"));
        m_TableModel->setHeaderData(5,Qt::Horizontal,tr("����ʱ��"));
    }
    if(ui->box_Kind->currentText() == tr("ע����¼"))
    {
        sql = tr("select memcardid,member.`name`,member.membertypeid,userinfo.nickname,handletime from memcarddetail "\
                 "left join userinfo on memcarddetail.operatorid = userinfo.userid left join member on memcarddetail.memcardid = member.cardid "\
                 "where memcarddetail.handletype = 7 and handletime between ('%1') and ('%2')")
                .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        if(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt() != 0)
        {
            sql.append(tr(" and memcarddetail.operatorid = '%1'").arg(ui->box_Server->itemData(ui->box_Server->currentIndex()).toInt()));
        }
        if(!ui->lineEdit_Cardid->text().isEmpty())
        {
            sql.append(tr(" and memcarddetail.memcardid = '%1'").arg(ui->lineEdit_Cardid->text()));
        }
        qDebug()<<"card detail:"<<sql;
        ((QSqlQueryModel*)m_TableModel)->setQuery(sql,*getSqlManager()->getdb());
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("ע������"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("�û���"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("�û�����"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("ע������Ա"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("ע��ʱ��"));
    }
}

void CardDetailWidget::on_but_ToExcel_clicked()
{

}
