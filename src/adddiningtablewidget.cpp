#include "adddiningtablewidget.h"
#include "ui_adddiningtablewidget.h"
#include <QMessageBox>
#include "sqlmanager.h"
AddDiningTableWidget::AddDiningTableWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDiningTableWidget)
{
    ui->setupUi(this);
}

AddDiningTableWidget::~AddDiningTableWidget()
{
    delete ui;
}


void AddDiningTableWidget::showEvent(QShowEvent *)
{
    m_newName.clear();
    ui->lineEdit_2->clear();
    //生成新的编号
    QString sql = tr("select max(id) from diningtable");
    QSqlQuery *query = getSqlManager()->ExecQuery(sql);
    if(query)
    {
        if(query->next())
        {
            QString maxId = query->value(0).toString();
            ui->lineEdit->setText(tr("%1").arg(maxId.toInt() + 1, 4, 10, QLatin1Char('0')));
        }
    }
}

void AddDiningTableWidget::on_toolButton_clicked()
{
    m_newId = ui->lineEdit->text();
    m_newName = ui->lineEdit_2->text();
    if(m_newName.isEmpty())
    {
        QMessageBox::information(this, "提示", "餐桌名称不能为空");
    }
    else
    {
        this->accept();
    }
}
