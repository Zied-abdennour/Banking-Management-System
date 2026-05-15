#include "manageloans.h"
#include "data.h"
#include "loanmeth.h"
#include "ui_manageloans.h"
#include "employeemenu.h"
#include <qdatetime.h>

manageloans::manageloans(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::manageloans)
{
    ui->setupUi(this);

    employeemenu *ep = qobject_cast<employeemenu*>(this->parentWidget());
    sw = qobject_cast<secondwindow2*>(ep->parentWidget());
    mw = qobject_cast<MainWindow*>(sw->parentWidget());

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    loadr();
}

manageloans::~manageloans()
{
    delete ui;
}

void manageloans::on_tableWidget_cellActivated(int row, int column)
{

}

void manageloans::loadr()
{
    ui->tableWidget->setRowCount(0);

    rloan req;
    int rowIndex = 0;


    for (int i = 0; i < mw->customers.ncust; i++)
    {
        customer &c = mw->customers.cust[i];

        if (c.acc.requestl == nullptr){
            continue;
        }
        {
            req = *(c.acc.requestl);
            ui->tableWidget->insertRow(rowIndex);
            string ch = "Loan " + to_string(i + 1);
            ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(QString::fromStdString(ch)));
            ui->tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(c.acc.AccountNumber));
            ui->tableWidget->setItem(rowIndex, 2, new QTableWidgetItem(req.LoanType));
            ui->tableWidget->setItem(rowIndex, 3, new QTableWidgetItem(QString::number(req.PrincipalAmount)));
            ui->tableWidget->setItem(rowIndex, 4, new QTableWidgetItem(QString::number(req.InterestRate)));
            ui->tableWidget->setItem(rowIndex, 5, new QTableWidgetItem(QString::number(req.MonthlyPayment)));
            ui->tableWidget->setItem(rowIndex, 6, new QTableWidgetItem(req.StartDate));
            ui->tableWidget->setItem(rowIndex, 7, new QTableWidgetItem(req.EndDate));

            rowIndex++;
        }
    }

    if (rowIndex == 0){
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setText("No loan requests available.");
    }
    else{
        ui->l2->clear();
    }
}
void manageloans::on_c_clicked()
{
    ui->l1->clear();

    QString acc = ui->le->text();

    if (acc.isEmpty()) {
        ui->l1->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l1->setText("Enter an Account Number!");
        return;
    }

    int index = -1;
    for (int i = 0; i < mw->customers.ncust; i++)
    {
        if (mw->customers.cust[i].acc.AccountNumber == acc)
        {
            index = i;
            break;
        }
    }

    if (index == -1) {
        ui->l1->setText("Invalid Account Number!");
        return;
    }

    if (!mw->customers.cust[index].acc.requestl) {
        ui->l1->setText("This customer has no loan request.");
        return;
    }

    ui->l1->setText("A loan request exists for \n this customer.");
}



void manageloans::on_c1_clicked()
{
    ui->l2->clear();

    QString acc = ui->le->text();
    QString option = ui->box->currentText();

    if (acc.isEmpty()) {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setText("Enter an Account Number!");
        return;
    }

    int index = -1;
    for (int i = 0; i < mw->customers.ncust; i++)
    {
        if (mw->customers.cust[i].acc.AccountNumber == acc)
        {
            index = i;
            break;
        }
    }

    if (index == -1) {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setText("Invalid Account Number!");
        return;
    }

    customer &c = mw->customers.cust[index];

    if (!c.acc.requestl) {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setText("This customer has no loan \n request!");
        return;
    }

    if (option == "Accept") {
        acceptReq(c, ui->l2);
        saveToCSVEdit(mw->customers,index);
    }
    else {
        declineReq(c, ui->l2);
        saveToCSVEdit(mw->customers,index);
    }

    loadr();
}



void manageloans::on_back_clicked()
{
    this->parentWidget()->show();
    this->hide();
}


void manageloans::on_exit_clicked()
{
    exit(1);
}

