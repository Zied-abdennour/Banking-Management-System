#include "modify.h"
#include "datae.h"
#include "employeemeth.h"
#include "mainwindow.h"
#include "ui_modify.h"

modify::modify(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::modify)
{
    ui->setupUi(this);
    ui->box->setVisible(false);

}

modify::~modify()
{
    delete ui;
}

void modify::on_confirm_clicked()
{
    bool ok;
    id=ui->le1->text().toInt(&ok);
    if (ok){

        onwhat = ui->Box->currentText();
        ui->l1->setText("Modifying on the employee"+QString::number(id)+" 's "+onwhat);
        ui->l2->setText("New "+onwhat+" :");
        ui->box->setVisible(true);
    }
    else{
        ui->l3->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l3->setStyleSheet("color: rgb(170,0,0);");
        ui->l3->setText("ID must be a number");
    }
}


void modify::on_back_clicked()
{
    ui->le1->clear();
    ui->le2->clear();
    ui->l1->clear();
    ui->l2->clear();
    ui->box->setVisible(false);
    this->parentWidget()->show();
    this->hide();
}


void modify::on_finish_clicked()
{
    ui->l3->clear();
    managermenu* mm = qobject_cast<managermenu*>(this->parentWidget());
    secondwindow3 * sw = qobject_cast<secondwindow3*>(mm->parentWidget());
    MainWindow* mw = qobject_cast<MainWindow*>(sw->parentWidget());
    employees es=mw->employees;
    int i=0;
    while(i<es.nemp && es.employees[i].Id!=id)
        i++;
    if (i>=es.nemp){
        ui->l3->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l3->setStyleSheet("color: rgb(170,0,0);");
        ui->l3->setText("Wrong ID");
    }
    else if (modifyEmployee(mw->employees.employees[i],onwhat,ui->le2->text())){
        saveEmployeeEdit(mw->employees,i);
        ui->l3->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l3->setStyleSheet("color: rgb(85, 170, 127);");
        ui->l3->setText("Successful modification");
    }
    else{
        ui->l3->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l3->setStyleSheet("color: rgb(170,0,0);");
        ui->l3->setText("Modification failed");
    }
}


void modify::on_exit_clicked()
{
    exit(1);
}
