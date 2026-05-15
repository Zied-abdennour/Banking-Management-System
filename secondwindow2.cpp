#include "secondwindow2.h"
#include "./ui_secondwindow2.h"
#include "employeemeth.h"
#include"mainwindow.h"
secondwindow2::secondwindow2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::secondwindow2)
{
    ui->setupUi(this);
}

secondwindow2::~secondwindow2()
{
    delete ui;
}

void secondwindow2::on_btnBack_clicked()
{
    this->parentWidget()->show();
    this->hide();
}


void secondwindow2::on_btnLogin_clicked()
{
    QString username = ui->le1->text();
    QString password = ui->le2->text();
    MainWindow *mw = qobject_cast<MainWindow*>(this->parentWidget());
    int x = mw->employees.nemp;
    employee *es = mw->employees.employees;
    if (loginEmployee(es,x,username,password,ui->l)){
        this->hide();
        afterlogin=new employeemenu(this);
        afterlogin->show();
        ui->le1->clear();
        ui->le2->clear();

    }
}

