#include "toolwidget.h"
#include "toolbutton.h"
#include <QLabel>
#include <QHBoxLayout>

toolWidget::toolWidget(QWidget *parent) :
    QWidget(parent)
{
    toolButton *tbTiJian=new toolButton(":/img/toolWidget/tiJian.png",tr("电脑体检"));
    toolButton *tbMuMa=new toolButton(":/img/toolWidget/muMa.png",tr("木马查杀"));
    toolButton *tbLouDong=new toolButton(":/img/toolWidget/louDong.png",tr("漏洞修复"));
    toolButton *tbXiTong=new toolButton(":/img/toolWidget/xiTong.png",tr("系统修复"));
    toolButton *tbQingLi=new toolButton(":/img/toolWidget/qingLi.png",tr("电脑清理"));
    toolButton *tbJiaSu=new toolButton(":/img/toolWidget/jiaSu.png",tr("优化加速"));
    toolButton *tbMenZhen=new toolButton(":/img/toolWidget/menZhen.png",tr("电脑门诊"));
    toolButton *tbRuanJian=new toolButton(":/img/toolWidget/ruanJian.png",tr("软件管家"));
    toolButton *tbGongNeng=new toolButton(":/img/toolWidget/gongNeng.png",tr("功能大全"));

    QLabel *logoLabel=new QLabel;
    QPixmap pixmap(":/img/logo.png");
    logoLabel->setPixmap(pixmap);
    logoLabel->setFixedSize(pixmap.size());
    logoLabel->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->setContentsMargins(5,0,5,0);
    mainLayout->addWidget(tbTiJian);
    mainLayout->addWidget(tbMuMa);
    mainLayout->addWidget(tbLouDong);
    mainLayout->addWidget(tbXiTong);
    mainLayout->addWidget(tbQingLi);
    mainLayout->addWidget(tbJiaSu);
    mainLayout->addWidget(tbMenZhen);
    mainLayout->addWidget(tbRuanJian);
    mainLayout->addWidget(tbGongNeng);
    mainLayout->addStretch();
    mainLayout->addWidget(logoLabel);
    setLayout(mainLayout);

    setFixedHeight(80);
}
