#include "toolwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVariant>
toolWidget::toolWidget(QWidget *parent) :
    QWidget(parent)
{
    m_buttonList.append(new toolButton(":/img/toolWidget/tiJian.png",tr("��    ҳ")));
    m_buttonList.append(new toolButton(":/img/toolWidget/louDong.png",tr("��˹���")));
    m_buttonList.append(new toolButton(":/img/toolWidget/muMa.png",tr("��Ա����")));
    m_buttonList.append(new toolButton(":/img/toolWidget/louDong.png",tr("�����̵�")));

//    m_buttonList.append(new toolButton(":/img/toolWidget/xiTong.png",tr("ϵͳ�޸�")));
//    m_buttonList.append(new toolButton(":/img/toolWidget/qingLi.png",tr("��������")));


    QLabel *logoLabel=new QLabel;
    QPixmap pixmap(":/img/logo.png");
    logoLabel->setPixmap(pixmap);
    logoLabel->setFixedSize(pixmap.size());
    logoLabel->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->setContentsMargins(5,0,5,0);
    foreach(toolButton *button, m_buttonList)
    {
        button->setStyleSheet("color: rgb(255, 255, 255);");
        mainLayout->addWidget(button);
    }
    mainLayout->addStretch();
    mainLayout->addWidget(logoLabel);
    setLayout(mainLayout);

    setFixedHeight(80);
}

void toolWidget::connectToWidget(QObject *receiver)
{
    for(int i = 0; i < m_buttonList.count(); i++)
    {
        m_buttonList[i]->setProperty("index", i);
        connect(m_buttonList[i], SIGNAL(myToolClicked()), receiver, SLOT(changePage()));
    }
}
