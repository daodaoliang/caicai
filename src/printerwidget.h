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
    //�볡�¼�
    void EnterWidget(QWidget *data);
protected:
    QPoint move_point; //�ƶ��ľ���
    bool mouse_press; //��갴��
    //��갴���¼�
    void mousePressEvent(QMouseEvent *event);
    //����ͷ��¼�
    void mouseReleaseEvent(QMouseEvent *event);
    //����ƶ��¼�
    void mouseMoveEvent(QMouseEvent *event);
private slots:
    void on_pushButton_clicked();

private:
    Ui::PrinterWidget *ui;
};

#endif // PRINTERWIDGET_H
