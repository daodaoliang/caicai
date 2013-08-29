#include "userwidget.h"
#include "ui_userwidget.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include "sqlmanager.h"
UserWidget::UserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWidget)
{
    ui->setupUi(this);
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::showEvent(QShowEvent *)
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

void UserWidget::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() ||
            ui->lineEdit_2->text().isEmpty() ||
            ui->lineEdit_3->text().isEmpty() ||
            ui->lineEdit_4->text().isEmpty())
    {
        QMessageBox::information(this, "提示", "请输入完整信息");
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        return;
    }
    if(ui->lineEdit_3->text() != ui->lineEdit_4->text())
    {
        QMessageBox::information(this, "提示", "新密码输入不一致");
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        return;
    }
    QString userId = ui->lineEdit->text();

    QString oldPassword = QCryptographicHash::hash(tr("%1%2").arg(userId)
                                                   .arg(ui->lineEdit_2->text()).toLocal8Bit(),
                                                   QCryptographicHash::Md5).toHex().data();
    QString sql = tr("select count(*) from userinfo where username = '%1' and password = '%2'")
            .arg(userId).arg(oldPassword);
    QSqlQuery query = getSqlManager()->execQuery(sql);
    if(query.next() && query.value(0).toInt() == 1)
    {
        QString newPassword = QCryptographicHash::hash(tr("%1%2").arg(userId)
                                                       .arg(ui->lineEdit_3->text()).toLocal8Bit(),
                                                       QCryptographicHash::Md5).toHex().data();
        sql = tr("update userinfo set password = '%1' where username = '%2'")
                .arg(newPassword).arg(userId);
        query = getSqlManager()->execQuery(sql);
        if(query.numRowsAffected() == 1)
        {
            QMessageBox::information(this, "提示", "修改成功！新密码已经生效");
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
        }
    }
    else
    {
        QMessageBox::information(this, "提示", "密码验证错误");
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        return;
    }

}
