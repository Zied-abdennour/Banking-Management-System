#include "deposit.h"
#include "data.h"
#include "ui_deposit.h"
#include "mainwindow.h"
#include "secondwindow1.h"
#include "customer.h"
#include"accountmeth.h"
#include <QDebug>
deposit::deposit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::deposit)
{
    ui->setupUi(this);
    thirdwindow12 *tw = qobject_cast<thirdwindow12*>(this->parentWidget());
    sw = qobject_cast<secondwindow1*>(tw->parentWidget());
    mw = qobject_cast<MainWindow*>(sw->parentWidget());
    int index = sw->index;
    customer c = mw->customers.cust[index];
    ui->l1->setText(QString::number(c.acc.Balance));
    ui->l3->setText(c.acc.AccountNumber);
}

deposit::~deposit()
{
    delete ui;
}




void deposit::on_exit_clicked()
{
    exit(1);
}


void deposit::on_back_clicked()
{
    ui->l2->clear();
    this->parentWidget()->show();
    this->hide();
}


void deposit::on_submit_clicked()
{
    ui->l2->clear();
    thirdwindow12 *tw = qobject_cast<thirdwindow12*>(this->parentWidget());
    secondwindow1 *sw = qobject_cast<secondwindow1*>(tw->parentWidget());
    MainWindow *mw = qobject_cast<MainWindow*>(sw->parentWidget());
    int index=sw->index;
    customer &c = mw->customers.cust[index];
    if (index < 0 || index >= mw->customers.ncust) {
        return;
    }
    QString number=ui->le->text();
    int i=0;
    while (i<number.size() && '0' <=number[i] && number[i]<= '9'){
        i++;
    }
    ui->l1->setText(QString::number(c.acc.Balance));
    if (i>=number.size()){
        int amount= number.toInt();
        if (Deposit(c.acc, amount)){
            mw->customers.cust[index]=c;
            ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->l2->setStyleSheet("color: rgb(85, 170, 127);");
            ui->l2->setText("Deposit successful!");
            ui->l1->setText(QString::number(c.acc.Balance));
            saveToCSVEdit(mw->customers,index);
        }
        else{
            ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->l2->setStyleSheet("color: rgb(170,0,0);");
            ui->l2->setText("Failed to add transaction due \n to the insufficient space");
        }
    }
    else{
        ui->l2->setStyleSheet("color: rgb(170,0,0);");
        ui->l2->setText("Deposit failed!");
    }
}

