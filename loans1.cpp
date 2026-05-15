#include "loans1.h"
#include "data.h"
#include "datae.h"
#include "displayloans.h"
#include "loanmeth.h"
#include "mainwindow.h"
#include "ui_loans1.h"

loans1::loans1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loans1)
{
    ui->setupUi(this);

    displayloans *dl = qobject_cast<displayloans*>(this->parentWidget());
    employeemenu *em = qobject_cast<employeemenu*>(dl->parentWidget());
    secondwindow2 *sw = qobject_cast<secondwindow2*>(em->parentWidget());
    MainWindow *mw = qobject_cast<MainWindow*>(sw->parentWidget());
    int j = dl->customerIndex;
    c = mw->customers.cust[j];
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    loadLoans();
}

loans1::~loans1()
{
    delete ui;
}

void loans1::on_back_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

void loans1::on_tableWidget_cellActivated(int row, int column)
{

}

void loans1::loadLoans()
{
    ui->tableWidget->setRowCount(0);
    int loanCount = listSize(c.acc.l);

    if (loanCount == 0) {
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(170, 0, 0);");
        ui->l->setText("No loans to display");
        return;
    }

    ui->l->clear();

    for (int i = 1; i <= loanCount; i++)
    {
        loan L = getElement(c.acc.l, i);
        int rowIndex = i - 1;

        ui->tableWidget->insertRow(rowIndex);

        std::string ch = "Loan " + std::to_string(i);
        ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(QString::fromStdString(ch)));
        ui->tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(L.LoanID));
        ui->tableWidget->setItem(rowIndex, 2, new QTableWidgetItem(L.LoanType));
        ui->tableWidget->setItem(rowIndex, 3, new QTableWidgetItem(QString::number(L.PrincipalAmount, 'f', 2)));
        ui->tableWidget->setItem(rowIndex, 4, new QTableWidgetItem(QString::number(L.InterestRate, 'f', 2)));
        ui->tableWidget->setItem(rowIndex, 5, new QTableWidgetItem(QString::number(L.AmountPaid, 'f', 2)));
        ui->tableWidget->setItem(rowIndex, 6, new QTableWidgetItem(QString::number(L.RemainingBalance, 'f', 2)));
        ui->tableWidget->setItem(rowIndex, 7, new QTableWidgetItem(QString::number(L.MonthlyPayment, 'f', 2)));
        ui->tableWidget->setItem(rowIndex, 8, new QTableWidgetItem(L.StartDate));
        ui->tableWidget->setItem(rowIndex, 9, new QTableWidgetItem(L.EndDate));
        ui->tableWidget->setItem(rowIndex, 10, new QTableWidgetItem(L.LoanStatus));
    }
}


void loans1::on_del_clicked()
{
    displayloans *dl = qobject_cast<displayloans*>(this->parentWidget());
    employeemenu *em = qobject_cast<employeemenu*>(dl->parentWidget());
    secondwindow2 *sw = qobject_cast<secondwindow2*>(em->parentWidget());
    MainWindow *mw = qobject_cast<MainWindow*>(sw->parentWidget());
    int j = dl->customerIndex;
    if (j < 0 || j >= mw->customers.ncust) {
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(170, 0, 0);");
        ui->l->setText("Error: Invalid customer index");
        return;
    }

    int completedCount = 0;
    int i = 1;
    while (i <= listSize(mw->customers.cust[j].acc.l))
    {
        loan L = getElement(mw->customers.cust[j].acc.l, i);
        if (L.LoanStatus == "Completed") {
            addl(&(mw->arch.completed_loans), L);
            removeAt(&(mw->customers.cust[j].acc.l), i);
            completedCount++;
        }
        else {
            i++;
        }
    }

    if (completedCount == 0) {
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(170, 0, 0);");
        ui->l->setText("No completed loans to transfer");
    } else {
        saveAllLoans(mw->arch.completed_loans);
        rewritec(mw->customers);
        readArchieveLoans(mw->arch);
        c = mw->customers.cust[j];
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(85, 170, 127);");
        ui->l->setText(QString("Transferred All completed loan(s)"));
        loadLoans();
    }
}

void loans1::on_submit_clicked()
{

    QString accountNum = ui->le->text();
    QString loanID = ui->le2->text();
    QString Status = ui->box->currentText();
    if (accountNum.isEmpty()) {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(170, 0, 0);");
        ui->l2->setText("Please enter Account Number");
        return;
    }

    if (loanID.isEmpty()) {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(170, 0, 0);");
        ui->l2->setText("Please enter Loan ID");
        return;
    }
    displayloans *dl = qobject_cast<displayloans*>(this->parentWidget());
    employeemenu *em = qobject_cast<employeemenu*>(dl->parentWidget());
    secondwindow2 *sw = qobject_cast<secondwindow2*>(em->parentWidget());
    MainWindow *mw = qobject_cast<MainWindow*>(sw->parentWidget());

    int j = dl->customerIndex;
    bool loanFound = false;
    int loanCount = listSize(mw->customers.cust[j].acc.l);

    for (int i = 1; i <= loanCount; i++) {
        loan L = getElement(mw->customers.cust[j].acc.l, i);

        if (L.LoanID == loanID) {
            loanFound = true;
            L.LoanStatus = Status;
            removeAt(&(mw->customers.cust[j].acc.l), i);
            addl(&mw->arch.completed_loans,L);
            rewritec(mw->customers);
            saveLoan(L);
            c = mw->customers.cust[j];
            ui->le->clear();
            ui->le2->clear();
            ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->l2->setStyleSheet("color: rgb(85, 170, 127);");
            ui->l2->setText("Loan status updated successfully");
            loadLoans();
            break;
        }
    }

    if (!loanFound) {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(170, 0, 0);");
        ui->l2->setText("Loan ID not found");
    }
}

