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
    QString bkPicName;//�����ڱ���ͼƬ������
    QPoint normalTopLeft;//������ʾ�Ĵ������Ͻ�����
private slots:
    void showMax();
    void showMin();
    void showSkinWidget();
    void setPicName(QString);
};

#endif // MAINWIDGET_H
