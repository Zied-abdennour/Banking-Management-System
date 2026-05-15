#include "thirdwindow11.h"
#include "ui_thirdwindow11.h"
#include "mainwindow.h"
#include "customermeth.h"
#include<QLabel>
#include <qdatetime.h>
thirdwindow11::thirdwindow11(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::thirdwindow11)
{
    ui->setupUi(this);
    ui->le1->setPlaceholderText("Enter your name");
    ui->le2->setPlaceholderText("Enter your Surname");
    ui->le3->setPlaceholderText("Enter your Adress");
    ui->le4->setPlaceholderText("Enter your Phone Number");
    ui->le5->setPlaceholderText("Enter your Email");
    ui->le6->setPlaceholderText("Create a Password");
    ui->le7->setPlaceholderText("Create a Username");
}

thirdwindow11::~thirdwindow11()
{
    delete ui;
}

void thirdwindow11::on_btnback_clicked()
{
    this->parentWidget()->show();
    this->hide();
}


void thirdwindow11::on_btncreate_clicked()
{
    QString name;
    QString surname;
    QString address;
    QString phone_number;
    QString email;
    QString password;
    QString username;
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    name=ui->le1->text();
    surname=ui->le2->text();
    address=ui->le3->text();
    phone_number=ui->le4->text();
    email=ui->le5->text();
    password=ui->le6->text();
    username=ui->le7->text();
    secondwindow1 *sw = qobject_cast<secondwindow1*>(this->parentWidget());
    MainWindow *mw = qobject_cast<MainWindow*>(sw->parentWidget());
    x = mw->customers.ncust;
    customer* cs = mw->customers.cust;
    if (registerCustomer(cs,x ,ui->l,name,surname,address,phone_number,email,password,username,date)){
        mw->customers.ncust=x;
        this->hide();
        afterregist= new afterregistering(this);
        afterregist->show();
    }
}
