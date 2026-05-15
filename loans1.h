#ifndef LOANS1_H
#define LOANS1_H

#include "customer.h"
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class loans1;
}

class loans1 : public QDialog
{
    Q_OBJECT

public:
    explicit loans1(QWidget *parent = nullptr);
    ~loans1();

private slots:
    void on_back_clicked();

    void on_tableWidget_cellActivated(int row, int column);

    void on_del_clicked();

    void on_submit_clicked();

private:
    Ui::loans1 *ui;
    secondwindow2* sw;
    MainWindow* mw;
    void loadLoans();
    customer c;
};

#endif // LOANS1_H
