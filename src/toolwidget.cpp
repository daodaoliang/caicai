#include "toolwidget.h"
#include <QLabel>
#include <QHBoxLayout>

toolWidget::toolWidget(QWidget *parent) :
    QWidget(parent)
{
    m_buttonList.append(new toolButton(":/img/toolWidget/tiJian.png",tr("点菜管理")));
    m_buttonList.append(new toolButton(":/img/toolWidget/muMa.png",tr("会员管理")));
    m_buttonList.append(new toolButton(":/img/toolWidget/louDong.png",tr("漏洞修复")));
    m_buttonList.append(new toolButton(":/img/toolWidget/xiTong.png",tr("系统修复")));
    m_buttonList.append(new toolButton(":/img/toolWidget/qingLi.png",tr("电脑清理")));


    QLabel *logoLabel=new QLabel;
    QPixmap pixmap(":/img/logo.png");
    logoLabel->setPixmap(pixmap);
    logoLabel->setFixedSize(pixmap.size());
    logoLabel->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->setContentsMargins(5,0,5,0);
    foreach(toolButton *button, m_buttonList)
    {
        mainLayout->addWidget(button);
    }
    mainLayout->addStretch();
    mainLayout->addWidget(logoLabel);
    setLayout(mainLayout);

    setFixedHeight(80);
}

void toolWidget::connectToWidget(QObject *receiver)
{
    //connect(receiver, SIGNAL(), )
}
