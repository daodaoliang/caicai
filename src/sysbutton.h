#ifndef SYSBUTTON_H
#define SYSBUTTON_H

#include <QPushButton>

class sysButton : public QPushButton
{
    Q_OBJECT
public:
    explicit sysButton(QString picName,QString tipText,QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    //枚举按钮的几种状态
    enum buttonStatus{NORMAL,ENTER,PRESS,NOSTATUS};
    buttonStatus status;
    QPixmap pixmap;

    int btnWidth;
    int btnHeight;

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);//鼠标进入
    void mousePressEvent(QMouseEvent *e);//按下鼠标
    void mouseReleaseEvent(QMouseEvent *e);//释放鼠标
    void leaveEvent(QEvent *);//鼠标离开
};

#endif // SYSBUTTON_H

/*
  最大化 最小化 关闭按钮
*/
