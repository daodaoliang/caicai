#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "sqlmanager.h"
LoginWidget::LoginWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit->text().isEmpty())
    {
        ui->label_3->setText("�û����������벻��Ϊ��");
    }
    QString user = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    int userId = 0;
    QString nickName = getSqlManager()->login(user, password, "000", userId);
    qApp->setProperty("userId", userId);
    if(!nickName.isEmpty())
    {
        this->accept();
    }
    else
    {
        ui->label_3->setText("��¼ʧ�ܻ����Ѿ���¼");
    }
}
