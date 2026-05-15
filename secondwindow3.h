#ifndef SECONDWINDOW3_H
#define SECONDWINDOW3_H
#include <QDialog>
#include"managermenu.h"

namespace Ui {
class secondwindow3;
}

class secondwindow3 : public QDialog
{
    Q_OBJECT

public:
    explicit secondwindow3(QWidget *parent = nullptr);
    ~secondwindow3();

private slots:
    void on_btnBack_clicked();

    void on_exit_clicked();

    void on_btnLogin_clicked();

private:
    Ui::secondwindow3 *ui;
    managermenu *mm;
};

#endif
