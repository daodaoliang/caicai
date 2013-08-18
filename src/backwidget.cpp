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

}
