#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui/QWidget>

class mainWidget : public QWidget
{
    Q_OBJECT
    
public:
    mainWidget(QWidget *parent = 0);
    ~mainWidget();

protected:
    void paintEvent(QPaintEvent *);
private:
    QString bkPicName;//主窗口背景图片的名称
    QPoint normalTopLeft;//正常显示的窗口左上角坐标
private slots:
    void showMax();
    void showMin();
    void showSkinWidget();
    void setPicName(QString);
};

#endif // MAINWIDGET_H
