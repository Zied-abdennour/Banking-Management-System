#include "add.h"
#include "datae.h"
#include "employeemeth.h"
#include "functions.h"
#include "mainwindow.h"
#include "ui_add.h"
#include <qdatetime.h>

add::add(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add)
{
    ui->setupUi(this);
    QStringList regions;
    regions << "Tunis" << "Ariana" << "Ben Arous" << "Manouba" << "Nabeul"<< "Zaghouan" << "Bizerte" << "Beja" << "Jendouba" << "Kef"
            << "Siliana" << "Sousse" << "Monastir" << "Mahdia" << "Sfax"
            << "Kairouan" << "Kasserine" << "Sidi Bouzid" << "Gabes"
            << "Medenine" << "Tataouine" << "Gafsa" << "Tozeur" << "Kebili";

    ui->bb->addItems(regions);
    ui->bb->setEditable(false);
}

add::~add()
{
    delete ui;
}


void add::on_exit_clicked()
{
    exit(1);
}

void add::on_Add_clicked()
{
    QString id = ui->id->text();
    double salary = ui->s->text().toDouble();
    QString name=ui->n->text();
    QString lastName= ui->ln->text();
    QString address=ui->adrs->text();
    QString hireDate= QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString bankBranch=ui->bb->currentText();
    QString username=ui->u->text();
    QString password=ui->p->text();
    if (!isAlpha(name) ||!isAlpha(lastName) ||!isDigital(id) ||salary==0)
    {
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(170,0,0);");
        ui->l->setText("Please ensure that all fields are \n filled properly");
    }
    else {
        managermenu* mm = qobject_cast<managermenu*>(this->parentWidget());
        secondwindow3 * sw = qobject_cast<secondwindow3*>(mm->parentWidget());
        MainWindow* mw = qobject_cast<MainWindow*>(sw->parentWidget());
        employee e;
        e.Address=address;
        e.Id=id.toInt();
        e.Salary=salary;
        e.Name=name;
        e.LastName=lastName;
        e.HireDate=hireDate;
        e.BankBranch=bankBranch;
        e.username=username;
        e.password=password;

        bool success = addEmployee(mw->employees,e);
        if (success) {
            saveEmployeeToCSV(e);
            ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->l->setStyleSheet("color: rgb(85, 170, 127);");
            ui->l->setText("Employee added successfully Total \n employees: " + QString::number(mw->employees.nemp));

            ui->id->clear();
            ui->n->clear();
            ui->ln->clear();
            ui->adrs->clear();
            ui->s->clear();
            ui->bb->clear();
            ui->u->clear();
            ui->p->clear();
        } else {
            ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
            ui->l->setStyleSheet("color: rgb(170,0,0);");
            ui->l->setText("Failed to add employee. ID or Username \n already exists.");
        }

    }

}

void add::on_back_clicked()
{
    this->parentWidget()->show();
    this->hide();

}


