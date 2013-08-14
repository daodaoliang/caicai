#ifndef MEMBERCUSTOMWIDGET_H
#define MEMBERCUSTOMWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class MemberCustomWidget;
}

class MemberCustomWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MemberCustomWidget(QWidget *parent = 0);
    ~MemberCustomWidget();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MemberCustomWidget *ui;
    QSqlQueryModel m_model;
};

inline MemberCustomWidget *memberCustomWidgetInstance()
{
    static MemberCustomWidget *w = NULL;
    if(w == NULL)
    {
        w = new MemberCustomWidget();
    }
    return w;
}

#endif // MEMBERCUSTOMWIDGET_H
