#include "vipwidget.h"
#include "ui_vipwidget.h"
#include "sqlmanager.h"
#include <QDebug>
#include <QSqlError>
#include <QTableView>
#include <QMessageBox>
#include "readonlydelegate.h"
#include "cardreadermanager.h"
#include <QStringList>
#include <QTableWidget>
#include <QHeaderView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QList>
#include <QSqlQuery>
#include "loginwidget.h"
VipWidget::VipWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VipWidget)
{
    ui->setupUi(this);
    //记载数据库信息到图表
    m_QueryModel = new QSqlQueryModel(this);
    m_TableModel = new QSqlTableModel(this,*getSqlManager()->getdb());
    m_TableModel->setTable("member");
    m_TableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置整个列表不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置选中模式为选中整行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //使用分页模式，第一次打开只显示前m_Interval条记录
    m_TableModel->select();
    //设置view的数据源
    ui->tableView->setModel(m_TableModel);
    //显示页信息
    resetPageInfo();
    //显示的列名
    m_TableModel->setHeaderData(0,Qt::Horizontal,tr("会员编号"));
    m_TableModel->setHeaderData(1,Qt::Horizontal,tr("会员卡号"));
    m_TableModel->setHeaderData(2,Qt::Horizontal,tr("会员姓名"));
    m_TableModel->setHeaderData(3,Qt::Horizontal,tr("会员电话"));
    m_TableModel->setHeaderData(4,Qt::Horizontal,tr("身份证号"));
    m_TableModel->setHeaderData(5,Qt::Horizontal,tr("注册时间"));
    m_TableModel->setHeaderData(6,Qt::Horizontal,tr("到期时间"));
    m_TableModel->setHeaderData(7,Qt::Horizontal,tr("会员类型"));
    m_TableModel->setHeaderData(8,Qt::Horizontal,tr("所属分店"));
    m_TableModel->setHeaderData(9,Qt::Horizontal,tr("账户余额"));
    //用此方法壳设置某列不可编辑
    ui->tableView->setItemDelegateForColumn(0,new readonlyDelegate(this));
    ui->tableView->setItemDelegateForColumn(1,new readonlyDelegate(this));
    ui->tableView->setItemDelegateForColumn(5,new readonlyDelegate(this));
    ui->tableView->setItemDelegateForColumn(9,new readonlyDelegate(this));
    //设置列不显示
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(6,true);
    //设置点击标题排序
    QHeaderView* header = ui->tableView->horizontalHeader();
    header->setSortIndicator(0,Qt::AscendingOrder);
    header->setSortIndicatorShown(true);
    header->setClickable(true);
    //connect(header,SIGNAL(sectionClicked(int)),this,SLOT(slot_Sort(int)));
    //
    m_CurCardSnr = "";
    //加载数据库会员类型到下拉列表
    m_BoxMap.clear();
    loadComBox();
    //默认充值消费不可用,只有打开卡片确认有该用户后充值按钮可用
    ui->but_Recharge->setEnabled(false);
    ui->but_pay->setEnabled(false);
    //初始化操作员
    m_nOperid = 0;
    m_Sql = "";
}

VipWidget::~VipWidget()
{
    delete ui;
    delete m_TableModel;
    delete m_QueryModel;
}

void VipWidget::on_pushButton_Add_clicked()
{
    QString shopid = ui->lineEdit_ShopID->text();
    QString memName = ui->lineEdit_MemName->text();
    QString nmemType = ui->Box_MemType->currentText();
    int memType = 0;
    if(!m_BoxMap.contains(nmemType))
    {
        qDebug()<<"has no box";
        memType = 1;
    }else
    {
        qDebug()<<nmemType<<m_BoxMap.values(nmemType).size()<<m_BoxMap.values(nmemType).at(0);
        memType = m_BoxMap.values(nmemType).at(0);
    }
    qDebug()<<"add memtype"<<memType;
    QString idCard = ui->lineEdit_IDCard->text();
    QString phone = ui->lineEdit_Phone->text();
    QString cardNum = ui->lineEdit_CardNum->text();
    if(shopid.length()==0||memName.length()==0||nmemType.length()==0||idCard.length()==0||phone.length()==0||ui->lineEdit_CardNum->text().length()==0)
    {
        return;
    }
    if(ui->pushButton_Add->text() == "添加")
    {
        if(selectVipInfoByCardID(cardNum) > 0)
        {
            QMessageBox::warning(NULL, tr("警告"), "该卡已注册会员！");
            return;
        }
        int rowCount = m_TableModel->rowCount();
        m_TableModel->insertRow(rowCount);
        m_TableModel->setData(m_TableModel->index(rowCount,1),cardNum);
        m_TableModel->setData(m_TableModel->index(rowCount,2),memName);
        m_TableModel->setData(m_TableModel->index(rowCount,3),phone);
        m_TableModel->setData(m_TableModel->index(rowCount,4),idCard);
        m_TableModel->setData(m_TableModel->index(rowCount,5),QDateTime::currentDateTime());
        m_TableModel->setData(m_TableModel->index(rowCount,7),memType);
        m_TableModel->setData(m_TableModel->index(rowCount,8),shopid);
        m_Sql = tr("insert into memcarddetail(memcardid,handletype,operatorid,handletime) valuse "\
                   "'%1','%2','%3','%4'")
                .arg(ui->lineEdit_CardNum->text()).arg(6).arg(m_nOperid)
                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    if(ui->pushButton_Add->text() == "修改")
    {
        QString sql = tr("update member set shopid=?,name=?,idcard=?,phone=?,membertypeid=? where cardid = '%1'").arg(cardNum);
        QSqlQuery query(*getSqlManager()->getdb());
        query.prepare(sql);
        query.bindValue(0,shopid);
        query.bindValue(1,memName);
        query.bindValue(2,idCard);
        query.bindValue(3,phone);
        query.bindValue(4,memType);
        m_QueryModel->setQuery(query);
        if(query.exec())
        {
            qDebug()<<"success--------------------------------------";
        }
        else
        {
            qDebug()<<"fail--------------------"<<query.lastError().text();
        }
    }
    setTextEnable(false);
}

void VipWidget::on_pushButton_2_clicked()
{
    if(!ui->tableView->currentIndex().isValid())
    {
        qDebug()<<"请选择要删除的行";
        return;
    }
    int curRow = ui->tableView->currentIndex().row();
    int curCol = ui->tableView->currentIndex().column();
    QString cardSnr = ui->tableView->model()->data(ui->tableView->model()->index(curRow,1)).toString();
    qDebug()<<"get card "<<cardSnr;
    if(cardSnr!= ui->lineEdit_CardNum->text())
    {
        qDebug()<<"卡序列号不同";
        return;
    }
    m_TableModel->removeRow(curRow);
    resetText();
    setTextEnable(true);
    m_Sql = tr("insert into memcarddetail(memcardid,handletype,operatorid,handletime) valuse "\
               "'%1','%2','%3','%4'")
            .arg(ui->lineEdit_CardNum->text()).arg(7).arg(m_nOperid)
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    //m_model->submitAll();
}
//每次保存都会重新获取界面会员信息写到卡中
void VipWidget::on_pushButton_Save_clicked()
{
    //TODO:如果顾客丢失会员卡进行卡注销(在会员类型中设置为0,丢失卡单独管理?)
    QSqlDatabase* db = getSqlManager()->getdb();
    QSqlQuery query(*db);
    if(db->transaction())
    {
        if(!writeInfoToCard())
        {
            qDebug()<<"保存信息到卡失败";
            m_TableModel->revertAll();
            m_Sql = "";
            return;
        }
        if(!m_TableModel->submitAll())
        {
            db->rollback();
            qDebug()<<"保存到数据库失败"<<m_TableModel->lastError().text();
        }
        if(!query.exec(m_Sql))
        {
            db->rollback();
        }
        if(!db->commit())
        {
            db->rollback();
        }
        resetText();
        setTextEnable(true);
        //添加或者删除后重新更新分页信息
        resetPageInfo();
        m_Sql = "";
    }

}

int VipWidget::selectVipInfoByCardID(const QString id)
{
    QString sql = tr("select count(*) from member");
    if(id != "")
    {
        sql = tr("select count(*) from member where cardid = '%1'").arg(id);
    }
    m_QueryModel->setQuery(sql,*getSqlManager()->getdb());
    while(m_QueryModel->query().next())
    {
        if(m_QueryModel->query().value(0).toInt() > 0 )
        {
            return m_QueryModel->query().value(0).toInt();
        }
    }
    m_QueryModel->clear();
    return 0;
}

bool VipWidget::writeInfoToCard()
{
    //unsigned int type = 0x0004;
    //返回卡序列号地址
    //unsigned long snr;
    //unsigned char size;
    QString key = "ffffffffffff";
    char tmp [16];
    memset(tmp,0,16);
    //QString cardID = "";
    //保存会员个人信息姓名到2扇区块8
    QString name = ui->lineEdit_MemName->text();
    memcpy(tmp,name.toLocal8Bit().data(),qMin(16,(int)strlen(name.toLocal8Bit().data())));
    if(!getCardReader()->WriteCard(key,8,tmp,16))
    {
        qDebug()<<"会员姓名写卡失败";
        return false;
    }
    //保存电话到2扇区块9
    QString phone = ui->lineEdit_Phone->text();
    memset(tmp,0,16);
    memcpy(tmp,phone.toLocal8Bit().data(),qMin(16,(int)strlen(phone.toLocal8Bit().data())));
    if(!getCardReader()->WriteCard(key,9,tmp,16))
    {
        qDebug()<<"电话写卡失败";
        return false;
    }
    //保存会员注册时间到2扇区块10
    QString starttime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    memset(tmp,0,16);
    memcpy(tmp,starttime.toLocal8Bit().data(),qMin(16,(int)strlen(starttime.toLocal8Bit().data())));
    if(!getCardReader()->WriteCard(key,10,tmp,16))
    {
        qDebug()<<"注册时间写卡失败";
        return false;
    }
    //保存身份证号前9位到3扇区12块
    QString idCard = ui->lineEdit_IDCard->text();
    QString bidCard = idCard.left(9);
    memset(tmp,0,16);
    memcpy(tmp,bidCard.toLocal8Bit().data(),(int)strlen(bidCard.toLocal8Bit().data()));
    if(!getCardReader()->WriteCard(key,12,tmp,16))
    {
        qDebug()<<"前身份证写卡失败写卡失败";
        return false;
    }
    //后9位或者6位到3扇区13块
    QString aidCard = idCard.right(idCard.length() - 9);
    memset(tmp,0,16);
    memcpy(tmp,aidCard.toLocal8Bit().data(),(int)strlen(aidCard.toLocal8Bit().data()));
    if(!getCardReader()->WriteCard(key,13,tmp,16))
    {
        qDebug()<<"后身份证写卡写卡失败";
        return false;
    }
    //保存会员类型到3扇区14块
    QString memtype = ui->Box_MemType->currentText();
    memset(tmp,0,16);
    memcpy(tmp,memtype.toLocal8Bit().data(),(int)strlen(memtype.toLocal8Bit().data()));
    if(!getCardReader()->WriteCard(key,14,tmp,16))
    {
        qDebug()<<"会员类型写卡失败";
        return false;
    }
    //保存分店编码到4扇区16块
    QString shopid = ui->lineEdit_ShopID->text();
    memset(tmp,0,16);
    memcpy(tmp,shopid.toLocal8Bit().data(),(int)strlen(shopid.toLocal8Bit().data()));
    if(!getCardReader()->WriteCard(key,16,tmp,16))
    {
        qDebug()<<"会员编号写卡失败";
        return false;
    }
    //getCardReader()->DevBeep(10);
    getCardReader()->Halt();
    return true;
}

void VipWidget::resetText()
{
    ui->lineEdit_CardNum->clear();
    ui->lineEdit_IDCard->clear();
    ui->lineEdit_MemName->clear();
    //ui->lineEdit_MemType->clear();
    ui->Box_MemType->setCurrentIndex(0);
    ui->lineEdit_Phone->clear();
    ui->lineEdit_ShopID->clear();
    ui->pushButton_Add->setText("添加");
    ui->but_Recharge->setEnabled(false);
    ui->but_pay->setEnabled(false);
}

void VipWidget::setTextEnable(bool enable)
{
    //ui->lineEdit_CardNum->setEnabled(enable);
    ui->lineEdit_IDCard->setEnabled(enable);
    ui->lineEdit_MemName->setEnabled(enable);
    ui->Box_MemType->setEnabled(enable);
    ui->lineEdit_Phone->setEnabled(enable);
    ui->lineEdit_ShopID->setEnabled(enable);
    ui->lineEdit_ShopID->setEnabled(enable);
}

void VipWidget::updateRecord(int startPage)
{
    QString filer = tr("1=1 LIMIT %1,%2").arg((startPage-1)*m_Interval).arg(m_Interval);
    qDebug()<<tr("start:%1end:%2").arg((startPage-1)*m_Interval).arg(startPage*m_Interval);
    m_TableModel->setFilter(filer);
    ui->label_PageInfo->setText(tr("第%2页/共%1页/%3条").arg(m_PageCount).arg(startPage).arg(m_RecordCount));
    if(m_CurPage == 1)
    {
        ui->but_PreviousPage->setEnabled(false);
    }
    if(m_CurPage == m_PageCount)
    {
        ui->but_NextPage->setEnabled(false);
    }
}

void VipWidget::loadComBox()
{
    ui->Box_MemType->clear();
    QStringList list;
    QString type ="";
    int tid = 0;
    QString sql = tr("select * from membertype");
    m_QueryModel->setQuery(sql,*getSqlManager()->getdb());
    while(m_QueryModel->query().next())
    {
        tid = m_QueryModel->query().value(0).toInt();
        type = m_QueryModel->query().value(1).toString();
        //list.append(type);
        if(!m_BoxMap.contains(type))
        {
            ui->Box_MemType->addItem(type);
            m_BoxMap.insert(type,ui->Box_MemType->count()-1);
            m_BoxMap.insert(type,tid);
            qDebug()<<"load"<<type<<tid<<ui->Box_MemType->count()-1;
        }
    }
}

void VipWidget::setPageCount()
{
    if(m_RecordCount%m_Interval != 0)
    {
        m_PageCount = m_RecordCount / m_Interval + 1;
        return;
    }
    m_PageCount = m_RecordCount / m_Interval;
}

void VipWidget::resetPageInfo()
{
    m_RecordCount = selectVipInfoByCardID("");
    setPageCount();
    m_CurPage = 1;
    updateRecord(m_CurPage);
}



void VipWidget::on_pushButton_OpenCard_clicked()
{
    LoginWidget w(this);
    w.setAuthType(LoginWidget::Login);
    if(!w.exec())
    {
        QMessageBox::information(this, "提示","验证失败");

        return;
    }
    m_nOperid = w.authId();
    unsigned int type = 0x0004;
    //返回卡序列号地址
    unsigned long snr;
    unsigned char size;
    QString key = "ffffffffffff";
    char rdata[16];
    QString cardID;
    memset(rdata,0,16);
    if(!getCardReader()->Reset(10))
    {
        qDebug()<<tr("reset false");
        return;
    }
    if(!getCardReader()->RequestCard(1,&type))
    {
        qDebug()<<tr("requestcard false");
        return;
    }
    if(!getCardReader()->AnticollCard(0,&snr))
    {
        qDebug()<<tr("anticollcard false");
        return;
    }
    if(!getCardReader()->SelectCard(snr,&size))
    {
        qDebug()<<tr("selectcard false");
        return;
    }
    cardID = QString::number(snr);
    //
    if(getCardReader()->ReadCard(key,8,rdata,16,cardID))
    {
        ui->lineEdit_CardNum->setText(cardID);
        m_CurCardSnr = cardID;
        ui->lineEdit_MemName->setText(QString::fromLocal8Bit(rdata));
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,9,rdata,16,cardID))
    {
        ui->lineEdit_Phone->setText(QString::fromLocal8Bit(rdata));
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,10,rdata,16,cardID))
    {
        qDebug()<<QString::fromLocal8Bit(rdata);
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,12,rdata,16,cardID))
    {
        ui->lineEdit_IDCard->setText(QString::fromLocal8Bit(rdata));
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,13,rdata,16,cardID))
    {
        ui->lineEdit_IDCard->setText(ui->lineEdit_IDCard->text()+(QString::fromLocal8Bit(rdata)));
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,14,rdata,16,cardID))
    {
        //ui->lineEdit_MemType->setText(QString::fromLocal8Bit(rdata));
        if(m_BoxMap.contains(QString::fromLocal8Bit(rdata).at(1)))
        {
            ui->Box_MemType->setCurrentIndex(m_BoxMap.values(QString::fromLocal8Bit(rdata)).at(1));
        }
    }
    memset(rdata,0,16);
    if(getCardReader()->ReadCard(key,16,rdata,16,cardID))
    {
        ui->lineEdit_ShopID->setText(QString::fromLocal8Bit(rdata));
    }
    if(selectVipInfoByCardID(cardID) > 0)
    {
        //((QSqlQueryModel*)m_TableModel)->setQuery(tr("select * from member where cardid = '%1'").arg(cardID),*getSqlManager()->getdb());
        m_TableModel->setFilter(tr("cardid = '%1'").arg(cardID));
        ui->pushButton_Add->setText("修改");
        //        ui->but_NextPage->setEnabled(false);
        //        ui->but_PreviousPage->setEnabled(false);
        //        ui->but_Skip->setEnabled(false);
        ui->but_Recharge->setEnabled(true);
        ui->but_pay->setEnabled(true);
    }
    //getCardReader()->Halt();
    //getCardReader()->DevBeep(10);
    qDebug()<<"read:"<<QString::fromLocal8Bit(rdata)<<"ID:"<<cardID;
}

void VipWidget::on_pushButton_Cancle_clicked()
{
    m_TableModel->revertAll();
    resetText();
    setTextEnable(true);
    //((QSqlQueryModel*)m_TableModel)->setQuery(tr("select * from member LIMIT 10"),*getSqlManager()->getdb());
    resetPageInfo();
    m_Sql = "";
    //updateRecord(m_CurPage);
}

void VipWidget::on_but_NextPage_clicked()
{
    m_CurPage = m_CurPage + 1;
    ui->but_PreviousPage->setEnabled(true);
    updateRecord(m_CurPage);
}

void VipWidget::on_but_PreviousPage_clicked()
{
    m_CurPage = m_CurPage -1;
    ui->but_NextPage->setEnabled(true);
    updateRecord(m_CurPage);
}

void VipWidget::on_but_Skip_clicked()
{
    int page = ui->lineEdit_Skip->text().toInt();
    if(1 <= page && page <= m_PageCount)
    {
        updateRecord(page);
    }
    ui->lineEdit_Skip->clear();
}

void VipWidget::slot_Sort(int column)
{
    m_TableModel->setSort(column,Qt::AscendingOrder);
}

void VipWidget::on_but_Recharge_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->groupBox_2->setTitle(tr("充值信息"));
    ui->but_CancleCharge->setText("取消");
    ui->label_chong->setText(tr("充值金额："));
    ui->label_queren->setText(tr("确认金额："));
    ui->but_querenchong->setText(tr("充值"));
    m_QueryModel->clear();
    m_QueryModel->setQuery(tr("select balance from member where cardid = '%1'").arg(ui->lineEdit_CardNum->text()),*getSqlManager()->getdb());
    qDebug()<<ui->lineEdit_CardNum->text();
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    QFont font;
    font.setPointSize(30);
    while(m_QueryModel->query().next())
    {
        qDebug()<<"余额"<<m_QueryModel->query().value(0).toString();
        ui->label_yue->setText(m_QueryModel->query().value(0).toString());
        ui->label_yue->setPalette(pe);
        ui->label_yue->setFont(font);
    }
    m_QueryModel->clear();
    ui->but_Recharge->setEnabled(false);
    ui->but_pay->setEnabled(false);
}

void VipWidget::on_but_CancleCharge_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->groupBox_2->setTitle(tr("会员信息"));
    ui->but_Recharge->setEnabled(true);
    ui->but_pay->setEnabled(true);
    ui->lineEdit_chongzhi->clear();
    ui->lineEdit_querenchong->clear();
    ui->label_yue->clear();
    resetPageInfo();
    //updateRecord(m_CurPage);
}

void VipWidget::on_but_querenchong_clicked()
{
    m_QueryModel->clear();
    QString sql = "";
    QString sql2= "";
    double yue = 0;
    double chong = 0;
    double balance = 0;
    double more = 0;
    QString message = "";
    if((ui->lineEdit_querenchong->text() == ui->lineEdit_chongzhi->text()) && ui->lineEdit_chongzhi->text().length()!=0)
    {

        yue = ui->label_yue->text().toDouble();
        chong = ui->lineEdit_chongzhi->text().toDouble();
        more = ui->Edit_MoreMoney->text().toDouble();
    }
    else
    {
        return;
    }
    QSqlDatabase* db = getSqlManager()->getdb();
    QSqlQuery query(*db);
    if(ui->but_querenchong->text() == tr("充值"))
    {

        balance = yue+chong+more;
        sql = tr("update member set balance = '%1' where cardid = '%2'").arg(balance).arg(ui->lineEdit_CardNum->text());
        message = tr("充值成功!");
        //m_QueryModel->setQuery(sql,*getSqlManager()->getdb());
        sql2 = tr("insert into memcarddetail(memcardid,handletype,handlemoney,moremoney,operatorid,handletime) "\
                  "values '%1','%2','%3','%4','%5','%6'")
                .arg(ui->lineEdit_CardNum->text()).arg(1).arg(chong).arg(more).arg(m_nOperid).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    }
    else
        //if(ui->but_querenchong->text() == tr("扣款"))
    {

        message = tr("扣款成功!");
        if(chong > yue)
        {
            return;
        }
        balance = yue-chong;
        sql = tr("update member set balance = '%1' where cardid = '%2'").arg(balance).arg(ui->lineEdit_CardNum->text());
        sql2 = tr("insert into memcarddetail(memcardid,handletype,handlemoney,operatorid,handletime) "\
                  "values '%1','%2','%3','%4','%5','%6'")
                .arg(ui->lineEdit_CardNum->text()).arg(1).arg(chong).arg(m_nOperid).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    if(db->transaction())
    {
        m_QueryModel->setQuery(sql,*getSqlManager()->getdb());
        //query = getSqlManager()->ExecQuery(sql2);
        if(!query.exec(sql2))
        {
            db->rollback();
            return;
        }
        if(!db->commit())
        {
            return;
        }
        //        if(!m_QueryModel->lastError().isValid())
        //        {
        QMessageBox::warning(NULL, tr("提示"), message);
        ui->label_yue->setText(tr("%1").arg(balance));
        QPalette pe;
        pe.setColor(QPalette::WindowText,Qt::red);
        QFont font;
        font.setPointSize(30);
        ui->label_yue->setPalette(pe);
        ui->label_yue->setFont(font);
        ui->but_CancleCharge->setText("返回");
        ui->lineEdit_chongzhi->clear();
        ui->lineEdit_querenchong->clear();
        //}
    }
    else
    {
        db->rollback();
        return;
    }

}
QString VipWidget::payMoney(const double &money)
{
    on_pushButton_OpenCard_clicked();
    double yue = 0;
    m_QueryModel->clear();
    m_QueryModel->setQuery(tr("select balance from member where cardid = '%1'").arg(ui->lineEdit_CardNum->text()),*getSqlManager()->getdb());
    qDebug()<<ui->lineEdit_CardNum->text();
    if(m_QueryModel->query().next())
    {
        qDebug()<<"余额"<<m_QueryModel->query().value(0).toString();
        yue = m_QueryModel->query().value(0).toDouble();
    }
    else
    {
        return "";
    }
    if(yue < money)
    {
        return "";
    }
    double balance = yue - money;
    QString sql = tr("update member set balance = '%1' where cardid = '%2'").arg(balance).arg(ui->lineEdit_CardNum->text());
    m_QueryModel->setQuery(sql,*getSqlManager()->getdb());
    if(!m_QueryModel->lastError().isValid())
    {
        //ui->label_yue->setText(tr("%1").arg(balance));
        return ui->lineEdit_CardNum->text();
    }
    else
    {
        qDebug()<<m_QueryModel->lastError().text();
        return "";
    }
}
void VipWidget::on_but_pay_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->groupBox_2->setTitle(tr("消费信息"));
    ui->but_CancleCharge->setText("取消");
    ui->label_chong->setText(tr("消费金额："));
    ui->label_queren->setText(tr("确认金额："));
    ui->but_querenchong->setText(tr("扣款"));
    m_QueryModel->clear();
    m_QueryModel->setQuery(tr("select balance from member where cardid = '%1'").arg(ui->lineEdit_CardNum->text()),*getSqlManager()->getdb());
    qDebug()<<ui->lineEdit_CardNum->text();
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    QFont font;
    font.setPointSize(30);
    while(m_QueryModel->query().next())
    {
        qDebug()<<"余额"<<m_QueryModel->query().value(0).toString();
        ui->label_yue->setText(m_QueryModel->query().value(0).toString());
        ui->label_yue->setPalette(pe);
        ui->label_yue->setFont(font);
    }
    m_QueryModel->clear();
    ui->but_Recharge->setEnabled(false);
    ui->but_pay->setEnabled(false);
}
