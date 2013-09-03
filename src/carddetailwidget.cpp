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
    ui->box_Server->insertItem(ui->box_Server->count(),"全部",0);
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
        QMessageBox::information(this, "提示", "验证失败");
        functionWidget()->changePage(0);
    }
}

void CardDetailWidget::on_but_Search_clicked()
{
    QString sql = "";
    ui->label_Info->clear();
    m_TableModel->clear();
    if(ui->box_Kind->currentText() == tr("开卡记录"))
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
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("开卡卡号"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("用户名"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("用户类型"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("开卡服务员"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("开卡时间"));
    }
    if(ui->box_Kind->currentText() == tr("充值记录"))
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
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("充值卡号"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("用户名"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("用户类型"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("充值金额"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("优惠金额"));
        m_TableModel->setHeaderData(5,Qt::Horizontal,tr("充值服务员"));
        m_TableModel->setHeaderData(6,Qt::Horizontal,tr("充值时间"));
        m_QueryModel->setQuery(sql2,*getSqlManager()->getdb());
        QString total = "0";
        if(m_QueryModel->query().next())
        {
            total = m_QueryModel->query().value(0).toString();
        }
        QString text = (tr("日期:<font size='4' color='red'>%1至%2</font>    ")
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
        QString info = ui->box_Server->currentText()+tr(" 充值现金金额:<font size='6' color='red'><b>%1</b></font>元；")
                .arg(total);
        ui->label_Info->setText(text+info);
    }
    if(ui->box_Kind->currentText() == tr("消费记录"))
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
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("消费卡号"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("用户名"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("用户类型"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("消费金额"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("订单号"));
        m_TableModel->setHeaderData(5,Qt::Horizontal,tr("扣款服务员"));
        m_TableModel->setHeaderData(6,Qt::Horizontal,tr("消费时间"));
        m_QueryModel->setQuery(sql2,*getSqlManager()->getdb());
        QString total = "0";
        if(m_QueryModel->query().next())
        {
            total = m_QueryModel->query().value(0).toString();
        }
        QString text = (tr("日期:<font size='4' color='red'>%1至%2</font>    ")
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
        QString info = ui->box_Server->currentText()+tr(" 消费金额:<font size='6' color='red'><b>%1</b></font>元；")
                .arg(total);
        ui->label_Info->setText(text+info);
    }
    if(ui->box_Kind->currentText() == tr("退款记录"))
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
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("退款卡号"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("用户名"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("用户类型"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("退款金额"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("退款订单号"));
        m_TableModel->setHeaderData(5,Qt::Horizontal,tr("退款服务员"));
        m_TableModel->setHeaderData(6,Qt::Horizontal,tr("退款时间"));
        m_QueryModel->setQuery(sql2,*getSqlManager()->getdb());
        QString total = "0";
        if(m_QueryModel->query().next())
        {
            total = m_QueryModel->query().value(0).toString();
        }
        QString text = (tr("日期:<font size='4' color='red'>%1至%2</font>    ")
                    .arg(ui->dateTimeEdit_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(ui->dateTimeEdit_End->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
        QString info = ui->box_Server->currentText()+tr(" 退款金额:<font size='6' color='red'><b>%1</b></font>元；")
                .arg(total);
        ui->label_Info->setText(text+info);
    }
    if(ui->box_Kind->currentText() == tr("额度调整"))
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
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("调整卡卡号"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("用户名"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("用户类型"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("调整后金额"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("调整服务员"));
        m_TableModel->setHeaderData(5,Qt::Horizontal,tr("整服时间"));
    }
    if(ui->box_Kind->currentText() == tr("注销记录"))
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
        m_TableModel->setHeaderData(0,Qt::Horizontal,tr("注销卡号"));
        m_TableModel->setHeaderData(1,Qt::Horizontal,tr("用户名"));
        m_TableModel->setHeaderData(2,Qt::Horizontal,tr("用户类型"));
        m_TableModel->setHeaderData(3,Qt::Horizontal,tr("注销服务员"));
        m_TableModel->setHeaderData(4,Qt::Horizontal,tr("注销时间"));
    }
}

void CardDetailWidget::on_but_ToExcel_clicked()
{

}
