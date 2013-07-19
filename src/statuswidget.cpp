#include "statuswidget.h"
#include <QLabel>
#include <QHBoxLayout>

statusWidget::statusWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setStyleSheet("color: rgb(255, 255, 255);");
    QLabel *labelVersion=new QLabel(tr("主程序版本:1.0.0.0"));
    QLabel *labelHorse=new QLabel(tr(""));
    QLabel *labelUpdate=new QLabel(tr("检查更新"));
    QLabel *labelConn360=new QLabel(tr(""));

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(labelVersion);
    labelVersion->setContentsMargins(5,0,0,0);
    mainLayout->addWidget(labelHorse);
    mainLayout->addWidget(labelUpdate);
    mainLayout->addStretch();
    mainLayout->addWidget(labelConn360);
    labelConn360->setContentsMargins(0,0,40,0);
    setLayout(mainLayout);

    setFixedHeight(25);
}
