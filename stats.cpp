#include "stats.h"
#include "mainwindow.h"
#include "managermenu.h"
#include "ui_stats.h"
#include "statisticsmeth.h"

stats::stats(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::stats)
{
    ui->setupUi(this);
    ui->box1->addItem("Personal Loan", 0);
    ui->box1->addItem("Home Loan", 1);
    ui->box1->addItem("Car Loan", 2);
    ui->box1->addItem("Education Loan", 3);
    ui->box1->addItem("Commercial Loan", 4);
    ui->box1->addItem("Short-Term Loan", 5);
    ui->box1->setEditable(false);
    QStringList regions;
    regions << "Tunis" << "Ariana" << "Ben Arous" << "Manouba" << "Nabeul"<< "Zaghouan" << "Bizerte" << "Beja" << "Jendouba" << "Kef"
            << "Siliana" << "Sousse" << "Monastir" << "Mahdia" << "Sfax"
            << "Kairouan" << "Kasserine" << "Sidi Bouzid" << "Gabes"
            << "Medenine" << "Tataouine" << "Gafsa" << "Tozeur" << "Kebili";

    ui->box3->addItems(regions);
    ui->box3->setEditable(false);
    managermenu *mg = qobject_cast<managermenu*>(this->parentWidget());
    secondwindow3 *sw3 = qobject_cast<secondwindow3*>(mg->parentWidget());
    MainWindow *mw = qobject_cast<MainWindow*>(sw3->parentWidget());
    cs =mw->customers;
    es =mw->employees;
    ui->l1->setText(QString ::number(getTotalLoans(cs.cust,cs.ncust)));
    int i = getCustomerWithMostLoans(this->cs.cust, this->cs.ncust);
    if (i >= 0 && i < this->cs.ncust) {
        QString name = this->cs.cust[i].acc.AccountHolderName;
        ui->l5->setText(name);
    } else {
        ui->l5->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l5->setText("No Customer Available");
    }
    ui->l6->setText(cs.cust[getCustomerWithHighestBalance(cs.cust, cs.ncust)].acc.AccountHolderName);
    ui->l7->setText(cs.cust[getCustomerWithLowestBalance(cs.cust, cs.ncust)].acc.AccountHolderName);
    ui->l8->setText(QString ::number(es.nemp));
}

stats::~stats()
{
    delete ui;
}


void stats::on_c1_clicked()
{
    QString t = ui->box1->currentText();
    ui->l2->setText(QString ::number(countLoansByType(cs.cust,cs.ncust,t)));
}


void stats::on_c3_clicked()
{
    QString dateb =ui->db->date().toString("yyyy-MM-dd");
    QString datee= ui->de->date().toString("yyyy-MM-dd");
    ui->l4->setText(QString ::number(activeLoansByDate(cs.cust,cs.ncust,dateb,datee)));
}


void stats::on_c2_clicked()
{
    QString t = ui->box2->currentText();
    ui->l3->setText(QString ::number(countLoansByStatus(cs.cust,cs.ncust,t)));
}




void stats::on_back_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

void stats::on_c4_clicked()
{
    QString code = ui->box3->currentText();
    int count = 0;

    for (int i = 0; i < es.nemp; i++) {
        if (es.employees[i].BankBranch == code) {
            count++;
        }
    }

    ui->l9->setText(QString::number(count));
}

