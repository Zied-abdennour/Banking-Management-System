#include "dailytransaction.h"
#include "data.h"
#include "ui_dailytransaction.h"
#include "accountmeth.h"
#include <qdatetime.h>
dailytransaction::dailytransaction(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dailytransaction)
{
    ui->setupUi(this);
    ui->box->setVisible(false);
    thirdwindow12 *tw = qobject_cast<thirdwindow12*>(this->parentWidget());
    sw = qobject_cast<secondwindow1*>(tw->parentWidget());
    mw = qobject_cast<MainWindow*>(sw->parentWidget());
    loadTransactions();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

dailytransaction::~dailytransaction()
{
    delete ui;
}


void dailytransaction::on_undolast_clicked()
{
    ui->box->setVisible(true);
}

void dailytransaction::on_no_clicked()
{
    ui->box->setVisible(false);
}


void dailytransaction::on_yes_clicked()
{
    ui->l->clear();

    int index = sw->index;
    account &acc = mw->customers.cust[index].acc;
    TransactionArray &TA = acc.dailyTransactions;

    QString today = QDate::currentDate().toString("yyyy-MM-dd");

    if (TA.lastUndoDate == today) {
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(170,0,0);");
        ui->l->setText("You can only undo one transaction \n per day.");
        ui->box->setVisible(false);
        return;
    }

    if (undoLast(acc)) {
        TA.lastUndoDate = today;
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(85, 170, 127);");
        ui->l->setText("Transaction removed successfully");
        loadTransactions();
        saveToCSVEdit(mw->customers, index);
    } else {
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(170,0,0);");
        ui->l->setText("There is no transaction to remove");
    }

    ui->box->setVisible(false);
}






void dailytransaction::loadTransactions()
{
    customer c = mw->customers.cust[sw->index];
    TransactionArray TA = c.acc.dailyTransactions;
    if(TA.last >= 0){
        int rowCount = TA.last+1;
        ui->tableWidget->setRowCount(rowCount);
        for (int i = 0; i < rowCount; i++)
        {
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(TA.transactions[i].TID)));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(TA.transactions[i].number));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(TA.transactions[i].Type));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(TA.transactions[i].Amount)));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(TA.transactions[i].Date));
        }
        ui->l2->clear();
    }
    else {
        ui->tableWidget->setRowCount(0);
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setText("There is no transaction to display") ;
    }
}
void dailytransaction::on_tableWidget_cellActivated(int row, int column)
{

}

void dailytransaction::on_back_clicked()
{
    ui->l->clear();
    this->parentWidget()->show();
    this->hide();
}


void dailytransaction::on_exit_clicked()
{
    exit(1);
}
