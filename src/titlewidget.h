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

    void showSkin();//���������ť

public slots:

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private:
    QPoint pressedPoint;//��갴��ȥ�ĵ�
    bool isMove;

    myPushButton *btnSkin;
    sysButton *btnMenuBar;
    sysButton *btnMin;
    sysButton *btnMax;
    sysButton *btnClose;
};

#endif // TITLEWIDGET_H
