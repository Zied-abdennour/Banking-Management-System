#ifndef REQUESTLOAN_H
#define REQUESTLOAN_H
#include"loanlist.h"

#include <QDialog>

namespace Ui {
class requestloan;
}

class requestloan : public QDialog
{
    Q_OBJECT

public:
    explicit requestloan(QWidget *parent = nullptr);
    ~requestloan();

private slots:
    void on_b_clicked();

    void on_exit_clicked();

    void on_back_clicked();

    void on_b2_clicked();

private:
    Ui::requestloan *ui;
    rList rl;
};

#endif // REQUESTLOAN_H
