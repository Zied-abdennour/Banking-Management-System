#include "displayemployee.h"
#include "employeemeth.h"
#include "mainwindow.h"
#include "ui_displayemployee.h"

displayemployee::displayemployee(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::displayemployee)
{
    ui->setupUi(this);
}

displayemployee::~displayemployee()
{
    delete ui;
}

void displayemployee::on_c_clicked()
{
    managermenu* mm = qobject_cast<managermenu*>(this->parentWidget());
    secondwindow3 * sw = qobject_cast<secondwindow3*>(mm->parentWidget());
    MainWindow* mw = qobject_cast<MainWindow*>(sw->parentWidget());
    employees &es=mw->employees;
    if (ui->box->currentText() == "By Last Name") {
        sortEmployeesByLastName(es);
    }
    else if (ui->box->currentText() == "By Bank Branch") {
        sortEmployeesByBranch(es);
    }
    else if (ui->box->currentText() == "By Recent Recruited") {
        sortEmployeeBylastRecruited(es);
    }
    if (es.nemp > 0) {
        ui->tableWidget->setRowCount(es.nemp);
        for (int i = 0; i < es.nemp; i++)
        {
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem("Employee " + QString::number(i + 1)));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(es.employees[i].Name));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(es.employees[i].LastName));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(es.employees[i].Address));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(es.employees[i].Salary)));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(es.employees[i].HireDate));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(es.employees[i].BankBranch));
        }
        ui->l->clear();
    }
    else {
        ui->tableWidget->setRowCount(0);
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setStyleSheet("color: rgb(170,0,0);");
        ui->l->setText("There is no Employees to Display");
    }
}

void displayemployee::on_back_2_clicked()
{
    this->parentWidget()->show();
    this->hide();

}

void displayemployee::on_exit_2_clicked()
{
    exit(1);
}


void displayemployee::on_back_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

