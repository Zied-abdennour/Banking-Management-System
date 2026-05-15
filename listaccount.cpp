#include "listaccount.h"
#include "accountmeth.h"
#include "data.h"
#include "datae.h"
#include "mainwindow.h"
#include "ui_listaccount.h"

listaccount::listaccount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::listaccount)
{
    ui->setupUi(this);
    employeemenu *ep = qobject_cast<employeemenu*>(this->parentWidget());
    sw = qobject_cast<secondwindow2*>(ep->parentWidget());
    mw = qobject_cast<MainWindow*>(sw->parentWidget());
    ui->accounts_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    loadaccounts();
}

listaccount::~listaccount()
{
    delete ui;
}

void listaccount::on_back_clicked()
{
    this->parentWidget()->show();
    this->hide();
}


void listaccount::on_exit_clicked()
{
    exit(1);
}

void listaccount::loadaccounts()
{
    int rowCount = mw->customers.ncust;
    ui->accounts_2->setRowCount(rowCount);

    for (int i = 0; i < rowCount; i++) {
        customer c = mw->customers.cust[i];
        ui->accounts_2->setItem(i, 0, new QTableWidgetItem(c.acc.AccountNumber));
        ui->accounts_2->setItem(i, 1, new QTableWidgetItem(c.acc.AccountType));
        ui->accounts_2->setItem(i, 2, new QTableWidgetItem(c.acc.IBAN));
        ui->accounts_2->setItem(i, 3, new QTableWidgetItem(c.acc.BranchCode));
        ui->accounts_2->setItem(i, 4, new QTableWidgetItem(c.acc.AccountHolderName));
        ui->accounts_2->setItem(i, 5, new QTableWidgetItem(c.acc.OpeningDate));
        ui->accounts_2->setItem(i, 6, new QTableWidgetItem(QString::number(c.acc.Balance)));
        ui->accounts_2->setItem(i, 7, new QTableWidgetItem(c.acc.Status));
    }

    if (rowCount == 0) {
        ui->l3->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l3->setText("There are no accounts to display");
    } else {
        ui->l3->clear();
    }
}

void listaccount::on_submit_clicked()
{
    ui->l2->clear();
    QString id = ui->le->text();
    QString s = ui->box->currentText();
    int index1 = -1;
    for (int i = 0; i < mw->customers.ncust; ++i) {
        if (mw->customers.cust[i].acc.AccountNumber == id) {
            index1 = i;
            break;
        }
    }
    if (index1 == -1) {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(170,0,0);");
        ui->l2->setText("Please enter a valid ID and \n click Confirm.");
        return;
    }
    customer &c=mw->customers.cust[index1];
    QString currentStatus = c.acc.Status;
    if (currentStatus==s){
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(170,0,0);");
        ui->l2->setText("This Account is Already "+s);
    }
    else {
        c.acc.Status =s;
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(85, 170, 127);");
        ui->l2->setText("Now, This Account is "+s);
        saveToCSVEdit(mw->customers,index1);
        loadaccounts();
    }
}

void listaccount::on_del_clicked()
{
    ui->l2->clear();
    int closedCount = 0;

    for (int i = 0; i < mw->customers.ncust; i++) {
        if (mw->customers.cust[i].acc.Status == "Closed") {
            mw->arch.archivedacc[mw->arch.nacc] = mw->customers.cust[i].acc;
            mw->arch.nacc++;
            saveAccount(mw->customers.cust[i].acc);
            readArchieveAccounts(mw->arch);
            for (int j = i; j < mw->customers.ncust - 1; j++) {
                mw->customers.cust[j] = mw->customers.cust[j + 1];
            }
            mw->customers.ncust--;
            i--;
            closedCount++;
        }
    }

    if (closedCount == 0) {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(170,0,0);");
        ui->l2->setText("No closed accounts to delete");
    } else {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(0, 170, 0);");
        ui->l2->setText(QString("Deleted all closed account"));
        rewritec(mw->customers);
        loadaccounts();
    }
}



void listaccount::on_c1_clicked()
{
    QString id =ui->le2->text();
    int index2 = -1;
    for (int i = 0; i < mw->customers.ncust; ++i) {
        if (mw->customers.cust[i].acc.AccountNumber == id) {
            index2 = i;
            break;
        }
    }
    if (index2 == -1) {
        ui->l3->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l3->setStyleSheet("color: rgb(170,0,0);");
        ui->l3->setText("Please enter a valid ID and \n click Confirm.");
        return;
    }
    account &acc = mw->customers.cust[index2].acc;
    TransactionArray &TA = acc.dailyTransactions;
    while (TA.last >= 0) {
        undoLast(acc);
    }
    saveToCSVEdit(mw->customers, index2);
    ui->l3->setFont(QFont("Segoe UI", 14, QFont::Bold));
    ui->l3->setStyleSheet("color: rgb(85, 170, 127);");
    ui->l3->setText("Transaction removed successfully");
}


void listaccount::on_c2_clicked()
{
    QString id =ui->le2->text();
    int index2 = -1;
    for (int i = 0; i < mw->customers.ncust; ++i) {
        if (mw->customers.cust[i].acc.AccountNumber == id) {
            index2 = i;
            break;
        }
    }
    if (index2 == -1) {
        ui->l3->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l3->setStyleSheet("color: rgb(170,0,0);");
        ui->l3->setText("Please enter a valid ID and \n click Confirm.");
        return;
    }
    account &acc = mw->customers.cust[index2].acc;
    TransactionArray &TA = acc.dailyTransactions;

    if (undoLast(acc)) {
        ui->l3->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l3->setStyleSheet("color: rgb(85, 170, 127);");
        ui->l3->setText("Transaction removed successfully");
        saveToCSVEdit(mw->customers, index2);
    } else {
        ui->l3->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l3->setStyleSheet("color: rgb(170,0,0);");
        ui->l3->setText("There is no transaction to remove");
    }
}

