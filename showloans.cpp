#include "showloans.h"
#include "ui_showloans.h"
#include "mainwindow.h"
#include "secondwindow1.h"
#include "requestloan.h"
#include "customer.h"
#include"loanmeth.h"
showloans::showloans(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::showloans)
{
    ui->setupUi(this);
    req = new requestloan(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    loadLoans();
}

showloans::~showloans()
{
    delete ui;
}

void showloans::on_tableWidget_cellActivated(int row, int column)
{

}
void showloans::loadLoans()
{
    ui->tableWidget->setRowCount(0);
    ui->l->clear();
    thirdwindow12 *tw = qobject_cast<thirdwindow12*>(this->parentWidget());
    secondwindow1 *sw = qobject_cast<secondwindow1*>(tw->parentWidget());
    MainWindow *mw = qobject_cast<MainWindow*>(sw->parentWidget());
    int index = sw->index;
    customer &c = mw->customers.cust[index];
    int loanCount = c.acc.l.size;
    int rowIndex = 0;
    if (loanCount == 0) {
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(170, 0, 0);");
        ui->l->setText("There are no loans to display");
        return;
    }
    for (int i = 1; i <= loanCount; i++)
    {
        loan L = getElement(c.acc.l, i);
        int rowIndex = i - 1;

        ui->tableWidget->insertRow(rowIndex);

        QString ch = "Loan " + QString::number(i);
        ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(ch));
        ui->tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(L.LoanID));
        ui->tableWidget->setItem(rowIndex, 2, new QTableWidgetItem(L.LoanType));
        ui->tableWidget->setItem(rowIndex, 3, new QTableWidgetItem(QString::number(L.PrincipalAmount)));
        ui->tableWidget->setItem(rowIndex, 4, new QTableWidgetItem(QString::number(L.InterestRate)));
        ui->tableWidget->setItem(rowIndex, 5, new QTableWidgetItem(QString::number(L.RemainingBalance)));
        ui->tableWidget->setItem(rowIndex, 6, new QTableWidgetItem(QString::number(L.MonthlyPayment)));
        ui->tableWidget->setItem(rowIndex, 7, new QTableWidgetItem(L.StartDate));
        ui->tableWidget->setItem(rowIndex, 8, new QTableWidgetItem(L.EndDate));
        ui->tableWidget->setItem(rowIndex, 9, new QTableWidgetItem(L.LoanStatus));
    }
}
void showloans::on_loan_clicked()
{
    req->show();
    this->hide();
}

void showloans::on_back_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

