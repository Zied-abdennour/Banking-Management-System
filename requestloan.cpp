#include "requestloan.h"
#include "data.h"
#include "showloans.h"
#include "ui_requestloan.h"
#include <QDate>
#include <QDateTime>
#include"secondwindow1.h"
#include"mainwindow.h"
#include"math.h"
#include"loanmeth.h"
requestloan::requestloan(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::requestloan)
{
    rl.head = nullptr;
    rl.tail = nullptr;
    rl.size = 0;
    ui->setupUi(this);
    ui->box->addItem("Personal Loan", 0);
    ui->box->addItem("Home Loan", 1);
    ui->box->addItem("Car Loan", 2);
    ui->box->addItem("Education Loan", 3);
    ui->box->addItem("Commercial Loan", 4);
    ui->box->addItem("Short-Term Loan", 5);
    ui->box->setEditable(false);
    ui->db->setMinimumDate(QDate::currentDate());
    ui->db->setDate(QDate::currentDate());
    ui->de->setMinimumDate(QDate::currentDate());
    ui->de->setDate(QDate::currentDate());
    float annualInterestRate=0.05 ;
}

requestloan::~requestloan()
{
    delete ui;
}

void requestloan::on_b_clicked()
{
    ui->la->clear();
    QDate dateb = ui->db->date();
    QDate datee = ui->de->date();
    if (datee <= dateb) {
        ui->la->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->la->setStyleSheet("color: rgb(170, 0, 0);");
        ui->la->setText("End date must be after start date!");
        return;
    }
    bool ok;
    double x=ui->le->text().toDouble(&ok);
    if(!ok || x <= 0){
        ui->la->setText("Wrong amount");
    }
    else{
        showloans *sl = qobject_cast<showloans*>(this->parentWidget());
        thirdwindow12 *tw = qobject_cast<thirdwindow12*>(sl->parentWidget());
        secondwindow1 *sw = qobject_cast<secondwindow1*>(tw->parentWidget());
        MainWindow *mw = qobject_cast<MainWindow*>(sw->parentWidget());
        int index=sw->index;
        QString loanType = ui->box->currentText();
        double annualInterestRate;
        if (loanType == "Personal Loan") {
            annualInterestRate = 8.0;
        } else if (loanType == "Home Loan") {
            annualInterestRate = 4.5;
        } else if (loanType == "Car Loan") {
            annualInterestRate = 6.0;
        } else if (loanType == "Education Loan") {
            annualInterestRate = 3.5;
        } else if (loanType == "Commercial Loan") {
            annualInterestRate = 7.0;
        } else if (loanType == "Short-Term Loan") {
            annualInterestRate = 10.0;
        } else {
            annualInterestRate = 5.0;
        }
        double months=dateb.daysTo(datee)/30.0;
        double monthlyInterestRate = (annualInterestRate/100) / 12.0;
        double factor = pow(1 + monthlyInterestRate, months);
        double monthlyPayment = x * (monthlyInterestRate * factor) / (factor - 1);
        customer &c = mw->customers.cust[index];
        if (!c.acc.requestl){
            c.acc.requestl=new rloan;
            inirloan(*c.acc.requestl);
            QString loanType = ui->box->currentText();
            c.acc.requestl->LoanType=loanType;
            c.acc.requestl->MonthlyPayment=monthlyPayment;
            c.acc.requestl->InterestRate=annualInterestRate;
            c.acc.requestl->StartDate=dateb.toString("yyyy-MM-dd");
            c.acc.requestl->EndDate=datee.toString("yyyy-MM-dd");
            c.acc.requestl->PrincipalAmount = x;
            radd(&rl,*c.acc.requestl);
            ui->la->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->la->setStyleSheet("color: rgb(85, 170, 127);");
            ui->la->setText("your request is added");
            mw->customers.cust[index]= c;
            saveToCSVEdit(mw->customers,index);
        }
        else{
            ui->la->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->la->setStyleSheet("color: rgb(170,0,0);");
            ui->la->setText("you have already requested");
        }
    }
}


void requestloan::on_exit_clicked()
{
    exit(1);
}


void requestloan::on_back_clicked()
{
    ui->la->clear();
    this->parentWidget()->show();
    this->hide();
}


void requestloan::on_b2_clicked()
{
    ui->la->clear();

    QString loanType = ui->box->currentText();
    double annualInterestRate;
    if (loanType == "Personal Loan") {
        annualInterestRate = 8.0;
    } else if (loanType == "Home Loan") {
        annualInterestRate = 4.5;
    } else if (loanType == "Car Loan") {
        annualInterestRate = 6.0;
    } else if (loanType == "Education Loan") {
        annualInterestRate = 3.5;
    } else if (loanType == "Commercial Loan") {
        annualInterestRate = 7.0;
    } else if (loanType == "Short-Term Loan") {
        annualInterestRate = 10.0;
    } else {
        annualInterestRate = 5.0;
    }
    ui->l->setText(QString::number(annualInterestRate)+ " % per year");
}
