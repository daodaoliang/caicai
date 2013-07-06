#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit myPushButton(QString picName,QString tipText,QWidget *parent = 0);
    
signals:
    

private:
    QPixmap pixmap;
    int iconWidth;
    int iconHeight;

protected:
 //   void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void leaveEvent(QEvent *);
};

#endif // MYPUSHBUTTON_H

/*
  换肤按钮
*/
