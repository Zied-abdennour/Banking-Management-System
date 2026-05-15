#include "addcustomer.h"
#include "customermeth.h"
#include "data.h"
#include "mainwindow.h"
#include "employeemenu.h"
#include "secondwindow2.h"
#include "ui_addcustomer.h"
#include <qdatetime.h>

addcustomer::addcustomer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addcustomer)
{
    ui->setupUi(this);
    ui->le1_2->setPlaceholderText("Enter customer's name");
    ui->le2_2->setPlaceholderText("Enter customer's Surname");
    ui->le3_2->setPlaceholderText("Enter customer's Address");
    ui->le4_2->setPlaceholderText("Enter customer's Phone Number");
    ui->le5_2->setPlaceholderText("Enter customer's Email");
    ui->le6_2->setPlaceholderText("Create a Password");
    ui->le7_2->setPlaceholderText("Create a Username");

    ui->box->addItem("Checking", 0);
    ui->box->addItem("Savings", 1);
    ui->box->addItem("Student", 2);
    ui->box->addItem("Business", 3);

    QStringList regions;
    regions << "Tunis" << "Ariana" << "Ben Arous" << "Manouba" << "Nabeul"
            << "Zaghouan" << "Bizerte" << "Beja" << "Jendouba" << "Kef"
            << "Siliana" << "Sousse" << "Monastir" << "Mahdia" << "Sfax"
            << "Kairouan" << "Kasserine" << "Sidi Bouzid" << "Gabes"
            << "Medenine" << "Tataouine" << "Gafsa" << "Tozeur" << "Kebili";
    ui->box2->addItems(regions);
    ui->box2->setEditable(false);

    ui->groupBox->setVisible(true);
    ui->gbox->setVisible(false);
}

addcustomer::~addcustomer()
{
    delete ui;
}

void addcustomer::on_btncreate_2_clicked()
{
    QString name = ui->le1_2->text();
    QString surname = ui->le2_2->text();
    QString address = ui->le3_2->text();
    QString phone_number = ui->le4_2->text();
    QString email = ui->le5_2->text();
    QString password = ui->le6_2->text();
    QString username = ui->le7_2->text();
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    if (name.isEmpty() || surname.isEmpty() || address.isEmpty() ||
        password.isEmpty() || username.isEmpty()) {
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setText("Data shouldn't be an empty string");
        return;
    }

    employeemenu *em = qobject_cast<employeemenu*>(this->parentWidget());
    secondwindow2 *sw = qobject_cast<secondwindow2*>(em->parentWidget());
    MainWindow *mw = qobject_cast<MainWindow*>(sw->parentWidget());


    int x = mw->customers.ncust;
    customer* cs = mw->customers.cust;

    if (registerCustomer(cs, x, ui->l, name, surname, address,phone_number, email, password, username,date)) {
        mw->customers.ncust = x;
        ui->l->setText("");
        ui->groupBox->setVisible(false);
        ui->gbox->setVisible(true);
    }

}

void addcustomer::on_back_clicked()
{
    ui->gbox->setVisible(false);
    ui->groupBox->setVisible(true);
}

void addcustomer::on_finish_clicked()
{
    QString Name = ui->le11->text();
    QString AccountType = ui->box->currentText();
    QString code = ui->box2->currentText();
    if (Name.isEmpty()) {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(170,0,0);");
        ui->l2->setText("Account holder name cannot be empty");
        return;
    }
    bool validName = true;
    for (int i = 0; i < Name.size(); i++) {
        QChar ch = Name[i];
        if (!ch.isLetter() && ch != ' ') {
            validName = false;
            break;
        }
    }

    if (!validName) {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(170,0,0);");
        ui->l2->setText("Name should contain only \n letters and spaces");
        return;
    }
    employeemenu *em = qobject_cast<employeemenu*>(this->parentWidget());
    secondwindow2 *sw = qobject_cast<secondwindow2*>(em->parentWidget());
    MainWindow *mw = qobject_cast<MainWindow*>(sw->parentWidget());
    if (mw->customers.ncust == 0) {
        ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l2->setStyleSheet("color: rgb(170,0,0);");
        ui->l2->setText("Error: No customer data found");
        return;
    }
    customer& c = mw->customers.cust[mw->customers.ncust - 1];
    c.acc.AccountHolderName = Name;
    c.acc.AccountType = AccountType;
    c.acc.OpeningDate = this->date;
    c.acc.AccountNumber = QString::fromStdString("000"+to_string(mw->customers.ncust)+"111");
    c.acc.IBAN = "TN59" + c.acc.AccountNumber;
    c.acc.BranchCode = bankBranch(code);
    c.acc.dailyTransactions.last = -1;
    saveToCSV1(c);
    ui->l2->setFont(QFont("Segoe UI", 14, QFont::Bold));
    ui->l2->setStyleSheet("color: rgb(85, 170, 127);");
    ui->l2->setText("Customer and account created successfully!");
    ui->le1_2->clear();
    ui->le2_2->clear();
    ui->le3_2->clear();
    ui->le4_2->clear();
    ui->le5_2->clear();
    ui->le6_2->clear();
    ui->le7_2->clear();
    ui->le11->clear();
    ui->l->clear();

}

void addcustomer::on_btnback_2_clicked()
{
    this->parentWidget()->show();
    this->hide();

}



void addcustomer::on_b2_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

