#include "statuswidget.h"
#include <QLabel>
#include <QHBoxLayout>

statusWidget::statusWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *labelVersion=new QLabel(tr("������汾:8.7.0.2001"));
    QLabel *labelHorse=new QLabel(tr("����ľ���:20121-8-24"));
    QLabel *labelUpdate=new QLabel(tr("������"));
    QLabel *labelConn360=new QLabel(tr("δ������360�ư�ȫ����"));

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
