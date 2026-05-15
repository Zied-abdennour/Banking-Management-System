#ifndef SECONDWINDOW1_H
#define SECONDWINDOW1_H
#include <QDialog>
#include"thirdwindow11.h"
#include"thirdwindow12.h"
namespace Ui {
class secondwindow1;
}

class secondwindow1 : public QDialog
{
    Q_OBJECT

public:
    explicit secondwindow1(QWidget *parent = nullptr);
    ~secondwindow1();
    int index ;


private slots:
    void on_btnLogin_clicked();
    void on_btnCreateAccount_clicked();
    void on_btnBack_clicked();

private:
    Ui::secondwindow1 *ui;
    thirdwindow12 *afterlogin;
    thirdwindow11 *regist;
};

#endif

