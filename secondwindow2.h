#ifndef SECONDWINDOW2_H
#define SECONDWINDOW2_H

#include <QDialog>
#include "employeemenu.h"
namespace Ui {
class secondwindow2;
}

class secondwindow2 : public QDialog
{
    Q_OBJECT

public:
    explicit secondwindow2(QWidget *parent = nullptr);
    ~secondwindow2();

private slots:
    void on_btnBack_clicked();

    void on_btnLogin_clicked();

private:
    Ui::secondwindow2 *ui;
    employeemenu *afterlogin;
};

#endif
