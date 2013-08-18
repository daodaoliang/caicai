#include "backwidget.h"
#include "ui_backwidget.h"

BackWidget::BackWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
}

BackWidget::~BackWidget()
{
    delete ui;
}

void BackWidget::showData(const QString &tableId)
{
    m_tableId = tableId;
    //TODO:���������ʾ

    m_model.setHeaderData(0, Qt::Horizontal, "������");
    m_model.setHeaderData(1, Qt::Horizontal, "��Ʒ����");
    m_model.setHeaderData(2, Qt::Horizontal, "����");
    m_model.setHeaderData(3, Qt::Horizontal, "����");
    m_model.setHeaderData(4, Qt::Horizontal, "�µ�ʱ��");
    m_model.setHeaderData(5, Qt::Horizontal, "֧����ʽ");
    m_model.setHeaderData(6, Qt::Horizontal, "��ƷID");
    ui->tableView->hideColumn(6);
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
    if(payType == 0)
    {
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
        int id = m_model.index(ui->tableView->currentIndex().row(), 6).data().toInt();
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
        QString orderId = m_model.index(ui->tableView->currentIndex().row(), 0).data().toString();
        bool result = dishesInfoBllInstance()->backDish(orderId, id, count, operatorId, 0, "", m_tableId);
        if(result)
        {
            QMessageBox::information(this, "��ʾ", "�˲˳ɹ�");
        }
        else
        {
            QMessageBox::information(this, "��ʾ", "�˲�ʧ��");
        }
    }
    else
    {
        //TODO:���ﴦ���˲�

    }
}
