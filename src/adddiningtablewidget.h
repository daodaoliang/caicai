#ifndef ADDDININGTABLEWIDGET_H
#define ADDDININGTABLEWIDGET_H

#include <QDialog>

namespace Ui {
class AddDiningTableWidget;
}

class AddDiningTableWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddDiningTableWidget(QWidget *parent = 0);
    ~AddDiningTableWidget();
    QString newId()
    {
        return m_newId;
    }

    QString newName()
    {
        return m_newName;
    }

protected:
    void showEvent(QShowEvent *);
private slots:
    void on_toolButton_clicked();

private:
    Ui::AddDiningTableWidget *ui;
    QString m_newId;
    QString m_newName;
};

#endif // ADDDININGTABLEWIDGET_H
