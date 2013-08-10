#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "sqlmanager.h"
#include <QDebug>
#include <QSqlRecord>
#include <QCryptographicHash>
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

int LoginWidget::authId()
{
    return m_userId;
}

void LoginWidget::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit->text().isEmpty())
    {
        ui->label_3->setText("用户名或者密码不能为空");
    }
    QString user = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    if(m_authType == Login)
    {
        int userId = 0;
        QString nickName = getSqlManager()->login(user, password, "000", userId);
        qApp->setProperty("userId", userId);
        if(!nickName.isEmpty())
        {
            this->accept();
        }
        else
        {
            ui->label_3->setText("登录失败或者已经登录");
        }
    }
    else
    {
        if(m_authType == OperViPCard)
        {
            password = QCryptographicHash::hash(tr("%1%2").arg(user).arg(password).toLocal8Bit(), QCryptographicHash::Md5).toHex().data();
            QString nickname = "";
            QString sql = tr("select userid,nickname from userinfo where username = '%1' and password = '%2'").arg(user).arg(password);
            QSqlQuery* query = getSqlManager()->ExecQuery(sql);
            if(query != NULL)
            {
                if(query->next())
                {
                    if(query->record().count() > 0)
                    {
                        m_userId = query->value(0).toInt();
                        nickname = query->value(1).toString();
                        this->accept();
                    }
                }
            }
            if(nickname.isEmpty())
            {
                ui->label_3->setText("登录失败或者已经登录");
            }
        }
        else
        {
            static int indexCount = 0;
            if(indexCount == 3)
            {
                indexCount = 0;
                this->reject();
            }
            else
            {
                int result = getSqlManager()->auth(user, password, m_authType);
                if(result != -1)
                {
                    indexCount = 0;
                    m_userId = result;
                    this->accept();
                }
                else
                {
                    ui->label_3->setText("登录失败或者已经登录");
                    indexCount++;
                }
            }
        }
    }
}
