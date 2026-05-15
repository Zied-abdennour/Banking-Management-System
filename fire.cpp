#include "fire.h"
#include "employeemeth.h"
#include "mainwindow.h"
#include "managermenu.h"
#include "secondwindow3.h"
#include "ui_fire.h"

fire::fire(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fire)
{
    ui->setupUi(this);
    ui->le->setPlaceholderText("ID");
    ui->box->setVisible(false);
}

fire::~fire()
{
    delete ui;
}

void fire::on_fire_2_clicked()
{
    QString id=ui->le->text();
    ui->box->setVisible(true);
    ui->l1->setFont(QFont("Segoe UI", 14, QFont::Bold));
    ui->l1->setText("Are you sure you want to fire \n the employee : "+id);
}

void fire::on_back_clicked()
{
    this->parentWidget()->show();
    this->hide();
}


void fire::on_exit_clicked()
{
    exit(1);
}


void fire::on_no_clicked()
{
    ui->box->setVisible(false);
}


void fire::on_yes_clicked()
{
    ui->l2->clear();
    managermenu* mm = qobject_cast<managermenu*>(this->parentWidget());
    secondwindow3 * sw = qobject_cast<secondwindow3*>(mm->parentWidget());
    MainWindow* mw = qobject_cast<MainWindow*>(sw->parentWidget());
    fireEmployee(mw->employees,ui->le->text(),ui->l2);
}

