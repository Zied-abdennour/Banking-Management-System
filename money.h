#ifndef MONEY_H
#define MONEY_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class money;
}

class money : public QDialog
{
    Q_OBJECT

public:
    explicit money(QWidget *parent = nullptr);
    ~money();

private slots:
    void on_withdraw_clicked();

    void on_back_clicked();

    void on_exit_clicked();

private:
    Ui::money *ui;
    secondwindow1* sw;
    MainWindow* mw;
    int index;
};

#endif // MONEY_H
