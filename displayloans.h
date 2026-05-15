#ifndef DISPLAYLOANS_H
#define DISPLAYLOANS_H

#include "loans1.h"
#include <QDialog>

namespace Ui {
class displayloans;
}

class displayloans : public QDialog
{
    Q_OBJECT

public:
    explicit displayloans(QWidget *parent = nullptr);
    ~displayloans();
    int customerIndex;

private slots:
    void on_back_clicked();

    void on_exit_clicked();

    void on_btn1_clicked();

private:
    Ui::displayloans *ui;
    loans1 *l1;
};

#endif // DISPLAYLOANS_H
