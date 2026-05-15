#ifndef DAILYTRANSACTION_H
#define DAILYTRANSACTION_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class dailytransaction;
}

class dailytransaction : public QDialog
{
    Q_OBJECT

public:
    explicit dailytransaction(QWidget *parent = nullptr);
    ~dailytransaction();

private slots:

    void on_undolast_clicked();

    void on_no_clicked();

    void on_yes_clicked();

    void on_tableWidget_cellActivated(int row, int column);

    void on_back_clicked();

    void on_exit_clicked();

private:
    Ui::dailytransaction *ui;
    MainWindow *mw;
    secondwindow1 *sw;
    void loadTransactions();
};

#endif // DAILYTRANSACTION_H

