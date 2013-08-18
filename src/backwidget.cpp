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
    //TODO:这里添加显示

    m_model.setHeaderData(0, Qt::Horizontal, "订单号");
    m_model.setHeaderData(1, Qt::Horizontal, "菜品名称");
    m_model.setHeaderData(2, Qt::Horizontal, "数量");
    m_model.setHeaderData(3, Qt::Horizontal, "单价");
    m_model.setHeaderData(4, Qt::Horizontal, "下单时间");
    m_model.setHeaderData(5, Qt::Horizontal, "支付方式");
    m_model.setHeaderData(6, Qt::Horizontal, "菜品ID");
    ui->tableView->hideColumn(6);
}

void BackWidget::on_tableView_clicked(const QModelIndex &index)
{

}

void BackWidget::on_pushButton_2_clicked()
{
    if(!ui->tableView->currentIndex().isValid())
    {
        QMessageBox::information(this, "提示", "请选择要退的记录");
        return;
    }
    int payType = m_model.index(ui->tableView->currentIndex().row(), 5).data().toInt();
    if(payType == 0)
    {
        //现金退菜，已完成
        LoginWidget w(this);
        w.setAuthType(LoginWidget::BackDish);
        if(!w.exec())
        {
            QMessageBox::information(this, "提示","验证失败");

            return;
        }
        int operatorId = w.authId();
        if(!m_countWidget.exec())
        {
            return;
        }
        //获取ID和数量
        int id = m_model.index(ui->tableView->currentIndex().row(), 6).data().toInt();
        int count = m_model.index(ui->tableView->currentIndex().row(), 2).data().toInt();

        if(m_countWidget.getDishesCount() == 0)
        {
            QMessageBox::information(this, "提示","退菜数量不能为0");
            return;
        }
        if(count < m_countWidget.getDishesCount())
        {
            QMessageBox::information(this, "提示","退菜份数不能大于点菜份数");
            return;
        }
        count = m_countWidget.getDishesCount();
        QString orderId = m_model.index(ui->tableView->currentIndex().row(), 0).data().toString();
        bool result = dishesInfoBllInstance()->backDish(orderId, id, count, operatorId, 0, "", m_tableId);
        if(result)
        {
            QMessageBox::information(this, "提示", "退菜成功");
        }
        else
        {
            QMessageBox::information(this, "提示", "退菜失败");
        }
    }
    else
    {
        //TODO:这里处理卡退菜

    }
}
