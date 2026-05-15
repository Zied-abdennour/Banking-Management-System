#include "secondwindow3.h"
#include "ui_secondwindow3.h"

secondwindow3::secondwindow3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::secondwindow3)
{
    ui->setupUi(this);
}

secondwindow3::~secondwindow3()
{
    delete ui;
}

void secondwindow3::on_btnBack_clicked()
{
    this->parentWidget()->show();
    this->hide();
}


void secondwindow3::on_exit_clicked()
{
    exit(1);
}


void secondwindow3::on_btnLogin_clicked()
{
    QString u=ui->le1->text();
    QString p=ui->le2->text();
    if (u=="admin126" && p=="admin126"){
        mm= new managermenu(this);
        this->hide();
        mm->show();
        ui->le1->clear();
        ui->le2->clear();
        ui->l->clear();
    }
    else{
        ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        ui->l->setText("Only the manager have access to \n this window");
    }
}
