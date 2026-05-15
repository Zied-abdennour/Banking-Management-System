#ifndef EMPLOYEEMENU_H
#define EMPLOYEEMENU_H


#include <QPropertyAnimation>
#include <QEvent>
#include <QDialog>

namespace Ui {
class employeemenu;
}
class displayloans;
class manageloans;
class addcustomer;
class listaccount;
class employeemenu : public QDialog
{
    Q_OBJECT

public:
    explicit employeemenu(QWidget *parent = nullptr);
    ~employeemenu();

private slots:
    void on_b5_clicked();

    void on_b4_clicked();

    void on_b6_clicked();

    void on_b3_clicked();

    void on_b7_clicked();

    void on_b9_clicked();

    void on_b2_clicked();

private:
    Ui::employeemenu *ui;
    addcustomer * ac;
    listaccount * lc;
    displayloans *dl;
    manageloans *ml;
    void setupButtonAnimations();
    bool eventFilter(QObject *obj, QEvent *event) override;
    void animateButton(QPushButton* button, bool scaleUp);
};

#endif
