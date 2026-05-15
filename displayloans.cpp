#include "displayloans.h"
#include "customermeth.h"
#include "mainwindow.h"
#include "employeemenu.h"
#include "ui_displayloans.h"
#include <QDebug>

displayloans::displayloans(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::displayloans)
{
    ui->setupUi(this);
    ui->groupBox->setVisible(true);
    ui->label_2->setVisible(true);
}

displayloans::~displayloans()
{
    delete ui;
}

void displayloans::on_back_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

void displayloans::on_exit_clicked()
{
    exit(1);
}

void displayloans::on_btn1_clicked()
{
    ui->l->clear();
    QString accountNumber = ui->accn->text();
    employeemenu *em = qobject_cast<employeemenu*>(this->parentWidget());
    secondwindow2 *sw = qobject_cast<secondwindow2*>(em->parentWidget());
    MainWindow *mw = qobject_cast<MainWindow*>(sw->parentWidget());
    if (accountNumber.isEmpty()) {
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(255, 0, 0);");
        ui->l->setText("Please fill the account Number \n field");
        return;
    }
    int index = accountIndx(mw->customers, accountNumber);

    if (index == -1) {
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(255, 0, 0);");
        ui->l->setText("Customer not Found");
        return;
    }
    customerIndex = index;
    this->hide();
    loans1 *loansWindow = new loans1(this);
    loansWindow->show();
}

