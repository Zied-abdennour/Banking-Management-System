#ifndef ARCHIEVE_H
#define ARCHIEVE_H

#include "employee.h"
#include <QDialog>


namespace Ui {
class archieve;
}
class archieve : public QDialog
{
    Q_OBJECT

public:
    explicit archieve(QWidget *parent = nullptr);
    ~archieve();

private slots:
    void on_back_clicked();

    void on_exit_clicked();

    void on_accounts_2_cellActivated(int row, int column);

    void on_loans_2_cellActivated(int row, int column);

    void on_transactions_2_cellActivated(int row, int column);

private:
    Ui::archieve *ui;
    void loadAccounts();
    void loadLoans();
    void loadTransactions();
    archieved Arch;
};

#endif
