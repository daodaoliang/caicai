#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QWidget>

class toolButton : public QWidget
{
    Q_OBJECT
public:
    explicit toolButton(QString picName,QString text,QWidget *parent = 0);
    
signals:
    void myToolClicked();

public slots:
    
private:
    void setBkPalette(int);

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
};

#endif // TOOLBUTTON_H

/*
  电脑体检 木马查杀 漏洞修复 系统修复等
*/
