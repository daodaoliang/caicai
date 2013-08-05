#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include <QTreeWidgetItem>
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
