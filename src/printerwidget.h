#ifndef PRINTERWIDGET_H
#define PRINTERWIDGET_H

#include <QWidget>
#include <QPoint>
#include "printerprocesser.h"
namespace Ui {
class PrinterWidget;
}

class PrinterWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrinterWidget(QWidget *parent = 0);
    ~PrinterWidget();
    //入场事件
    void EnterWidget(QWidget *data);
protected:
    QPoint move_point; //移动的距离
    bool mouse_press; //鼠标按下
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
private slots:
    void on_pushButton_clicked();

private:
    Ui::PrinterWidget *ui;
};

#endif // PRINTERWIDGET_H
