#include "afterregistering.h"
#include "customermeth.h"
#include "ui_afterregistering.h"
#include "thirdwindow11.h"
#include"mainwindow.h"
#include"data.h"
#include "ui_afterregistering.h"
afterregistering::afterregistering(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::afterregistering)
{
    ui->setupUi(this);
    ui->box->addItem("Checking", 0);
    ui->box->addItem("Savings", 1);
    ui->box->addItem("Student", 2);
    ui->box->addItem("Business", 3);
    QStringList regions;
    regions << "Tunis" << "Ariana" << "Ben Arous" << "Manouba" << "Nabeul"<< "Zaghouan" << "Bizerte" << "Beja" << "Jendouba" << "Kef"
            << "Siliana" << "Sousse" << "Monastir" << "Mahdia" << "Sfax"
            << "Kairouan" << "Kasserine" << "Sidi Bouzid" << "Gabes"
            << "Medenine" << "Tataouine" << "Gafsa" << "Tozeur" << "Kebili";

    ui->box2->addItems(regions);
    ui->box2->setEditable(false);
}

afterregistering::~afterregistering()
{
    delete ui;
}


void afterregistering::on_finish_clicked()
{
    thirdwindow11 *tw = qobject_cast<thirdwindow11*>(this->parentWidget());
    QString Name=ui->le1->text();
    QString AccountType = ui->box->currentText();
    int i=0;
    while(i<Name.size() && ('A'<=Name[i] && 'Z'>=Name[i] || 'a'<=Name[i] && 'z'>=Name[i]  || Name[i]==' '))
        i++;
    if(i>=Name.size()){
        secondwindow1 *sw = qobject_cast<secondwindow1*>(tw->parentWidget());
        MainWindow *mw = qobject_cast<MainWindow*>(sw->parentWidget());
        customer c=mw->customers.cust[mw->customers.ncust-1];
        c.acc.AccountHolderName=Name;
        c.acc.AccountType=AccountType;
        c.acc.AccountNumber=QString::fromStdString("000"+to_string(mw->customers.ncust)+"111");
        c.acc.IBAN = "TN59"+c.acc.AccountNumber;
        QString code = ui->box2->currentText();
        c.acc.BranchCode=bankBranch(code);
        c.acc.dailyTransactions.last=-1;
        c.acc.dailyTransactions.lastUndoDate="";
        mw->customers.cust[mw->customers.ncust-1]=c;
        saveToCSV1(c);
        hide();
        secondwindow1 *loginpage=mw->customerLoginPage;
        loginpage->show();
    }
    else{
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setText("Wrong Name") ;
    }
}



void afterregistering::on_back_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

