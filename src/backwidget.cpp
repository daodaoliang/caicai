#include "backwidget.h"
#include "ui_backwidget.h"
#include "sqlmanager.h"
#include "vipwidget.h"
#include <QDebug>
BackWidget::BackWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

BackWidget::~BackWidget()
{
    delete ui;
}

void BackWidget::showData(const QString &tableId)
{


    QString sql = tr("select orderinfo.orderid, dishes.dishesname, orderdetail.dishescount, dishes.price,"\
                     "orderdetail.handletime, orderdetail.paytype, orderdetail.cardid,dishes.dishesid from orderdetail "\
                     "LEFT JOIN dishes on dishes.dishesid = orderdetail.dishesid "\
                     "LEFT JOIN orderinfo on orderinfo.orderid = orderdetail.orderid "\
                     "where (handletime BETWEEN '%1' and '%2') and orderinfo.tableid = '%3'")
            .arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(QDate::currentDate().addDays(1).toString("yyyy-MM-dd"))
            .arg(tableId);

    m_model.setQuery(sql,*getSqlManager()->getdb());
    m_model.setHeaderData(0, Qt::Horizontal, "������");
    m_model.setHeaderData(1, Qt::Horizontal, "��Ʒ����");
    m_model.setHeaderData(2, Qt::Horizontal, "����");
    m_model.setHeaderData(3, Qt::Horizontal, "����");
    m_model.setHeaderData(4, Qt::Horizontal, "�µ�ʱ��");
    m_model.setHeaderData(5, Qt::Horizontal, "֧����ʽ");
    //    m_model.setHeaderData(6, Qt::Horizontal, "��ƷID");
    //    ui->tableView->hideColumn(6);

    m_model.setHeaderData(6, Qt::Horizontal, "��Ա����");
    m_model.setHeaderData(7, Qt::Horizontal, "��ƷID");
    ui->tableView->hideColumn(7);
    qDebug()<<"�˲�"<<sql;
}

void BackWidget::on_tableView_clicked(const QModelIndex &index)
{

}

void BackWidget::on_pushButton_2_clicked()
{
    if(!ui->tableView->currentIndex().isValid())
    {
        QMessageBox::information(this, "��ʾ", "��ѡ��Ҫ�˵ļ�¼");
        return;
    }
    int payType = m_model.index(ui->tableView->currentIndex().row(), 5).data().toInt();

    //�ֽ��˲ˣ������
    LoginWidget w(this);
    w.setAuthType(LoginWidget::BackDish);
    if(!w.exec())
    {
        QMessageBox::information(this, "��ʾ","��֤ʧ��");

        return;
    }
    int operatorId = w.authId();
    if(!m_countWidget.exec())
    {
        return;
    }
    //��ȡID������
    int id = m_model.index(ui->tableView->currentIndex().row(), 7).data().toInt();
    int count = m_model.index(ui->tableView->currentIndex().row(), 2).data().toInt();

    if(m_countWidget.getDishesCount() == 0)
    {
        QMessageBox::information(this, "��ʾ","�˲���������Ϊ0");
        return;
    }
    if(count < m_countWidget.getDishesCount())
    {
        QMessageBox::information(this, "��ʾ","�˲˷������ܴ��ڵ�˷���");
        return;
    }
    count = m_countWidget.getDishesCount();

    double backMoney = m_model.index(ui->tableView->currentIndex().row(), 3).data().toDouble() * count;
    QString orderId = m_model.index(ui->tableView->currentIndex().row(), 0).data().toString();

    bool result = dishesInfoBllInstance()->backDish(orderId, id, count, operatorId, 0, "", m_tableId);
    if(result)
    {
        QMessageBox::information(this, "��ʾ", "����˲˳ɹ�");
    }
    else
    {
        QMessageBox::information(this, "��ʾ", "����˲�ʧ��");
    }
    if(payType == 1)
    {
        qDebug()<<"back money"<<backMoney;
        bool ret = vipWidget()->backMoney(m_model.index(ui->tableView->currentIndex().row(), 6).data().toString(),backMoney,orderId,operatorId);
        if(!ret)
        {
            QMessageBox::information(this, "��ʾ", tr("��Ա���˿%1 Ԫʧ��,���ֶ��������").arg(backMoney));
        }
        else
        {
            QMessageBox::information(this, "��ʾ", tr("��Ա���˿%1 Ԫ�ɹ�").arg(backMoney));
        }
    }

}
