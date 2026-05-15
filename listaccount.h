#ifndef LISTACCOUNT_H
#define LISTACCOUNT_H


#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class listaccount;
}

class listaccount : public QDialog
{
    Q_OBJECT

public:
    explicit listaccount(QWidget *parent = nullptr);
    ~listaccount();

private slots:
    void on_back_clicked();

    void on_exit_clicked();

    void on_submit_clicked();

    void on_del_clicked();

    void on_c1_clicked();

    void on_c2_clicked();

private:
    Ui::listaccount *ui;
    secondwindow2* sw;
    MainWindow* mw;
    void loadaccounts();
};

#endif // LISTACCOUNT_H
