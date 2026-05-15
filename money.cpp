#include "money.h"
#include "data.h"
#include "ui_money.h"
#include "customer.h"
#include"accountmeth.h"

money::money(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::money)
{
    ui->setupUi(this);
    thirdwindow12 *tw = qobject_cast<thirdwindow12*>(this->parentWidget());
    sw = qobject_cast<secondwindow1*>(tw->parentWidget());
    mw = qobject_cast<MainWindow*>(sw->parentWidget());
    index=sw->index;
    customer c = mw->customers.cust[index];
    ui->l1->setText(QString::number(c.acc.Balance));
    ui->l3->setText(c.acc.AccountNumber);
}

money::~money()
{
    delete ui;
}


void money::on_withdraw_clicked()
{
    ui->l2->clear();
    QString number;
    number=ui->le->text();
    int i=0;
    while (i<number.size() && '0' <=number[i] && number[i]<= '9'){
        i++;
    }
    if (i>=number.size()){
        int amount= number.toInt();
        customer c = mw->customers.cust[index];
        int r = withdraw(c.acc, amount);
        if (r == 0){
            ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->l2->setStyleSheet("color: rgb(170,0,0);");
            ui->l2->setText("Not Enough Balance !");
        }
        else if (r == 1){
            ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->l2->setStyleSheet("color: rgb(170,0,0);");
            ui->l2->setText("The Amount must be % 10");
        }
        else if (r == 2){
            ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->l2->setStyleSheet("color: rgb(170,0,0);");
            ui->l2->setText("You have reach your transactions Limit");
        }
        else if (r == 3){
            mw->customers.cust[index]=c;
            ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->l2->setStyleSheet("color: rgb(85, 170, 127);");
            ui->l2->setText("Withdraw successful ");
            ui->l1->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->l1->setText(QString::number(c.acc.Balance));
            saveToCSVEdit(mw->customers,index);
        }
    }
    else {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(170,0,0);");
        ui->l2->setText("Withdraw failed!");
    }
}


void money::on_exit_clicked()
{
    exit(1);
}


void money::on_back_clicked()
{
    ui->l2->clear();
    this->parentWidget()->show();
    this->hide();
}
