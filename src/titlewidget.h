#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>

class myPushButton;
class sysButton;

class titleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit titleWidget(QWidget *parent = 0);
    
signals:
    void showMin();
    void showMax();

    void showSkin();//点击换肤按钮

public slots:

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private:
    QPoint pressedPoint;//鼠标按下去的点
    bool isMove;

    myPushButton *btnSkin;
    sysButton *btnMenuBar;
    sysButton *btnMin;
    sysButton *btnMax;
    sysButton *btnClose;
};

#endif // TITLEWIDGET_H
