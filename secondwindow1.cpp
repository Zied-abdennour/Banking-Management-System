#include "secondwindow1.h"
#include "./ui_secondwindow1.h"
#include <QMessageBox>
#include<Qpixmap>
#include<Qstring>
#include"customermeth.h"
#include"mainwindow.h"
secondwindow1::secondwindow1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::secondwindow1)
{
    ui->setupUi(this);
}

secondwindow1::~secondwindow1()
{
    delete ui;
}

void secondwindow1::on_btnBack_clicked()
{
    this->parentWidget()->show();
    this->hide();

}


void secondwindow1::on_btnLogin_clicked()
{
    ui->l->clear();
    QString username = ui->le1->text();
    QString password = ui->le2->text();
    MainWindow *mw = qobject_cast<MainWindow*>(this->parentWidget());
    int x = mw->customers.ncust;
    customer* cs = mw->customers.cust;
    int customerIndex = loginCustomer(cs, x, username, password, ui->l);
    if (customerIndex >= 0) {
        this->index = customerIndex;
        this->hide();
        afterlogin = new thirdwindow12(this);
        afterlogin->show();
        ui->le1->clear();
        ui->le2->clear();
        ui->l->clear();
    }
}


void secondwindow1::on_btnCreateAccount_clicked()
{
    ui->l->clear();
    this->hide();
    regist= new thirdwindow11(this);
    regist->show();
    ui->le1->clear();
    ui->le2->clear();
    ui->l->clear();
}
