#ifndef SHOWLOANS_H
#define SHOWLOANS_H
#include "mainwindow.h"
#include "requestloan.h"

#include <QDialog>

namespace Ui {
class showloans;
}

class showloans : public QDialog
{
    Q_OBJECT

public:
    explicit showloans(QWidget *parent = nullptr);
    ~showloans();

private slots:
    void on_tableWidget_cellActivated(int row, int column);

    void on_loan_clicked();

    void on_back_clicked();

private:
    Ui::showloans *ui;
    requestloan *req;
    void loadLoans();
    secondwindow1* sw;
    MainWindow* mw;
    int index;
};

#endif
