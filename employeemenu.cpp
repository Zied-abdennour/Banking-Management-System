#include "employeemenu.h"
#include "addcustomer.h"
#include "data.h"
#include "datae.h"
#include "displayloans.h"
#include "listaccount.h"
#include "mainwindow.h"
#include "manageloans.h"
#include "ui_employeemenu.h"

employeemenu::employeemenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::employeemenu)
{
    ui->setupUi(this);
    setupButtonAnimations();
}
void employeemenu::setupButtonAnimations() {
    QList<QPushButton*> buttons = {
        ui->b2,
        ui->b3,
        ui->b4,
        ui->b5,
        ui->b6,
        ui->b7,
        ui->b9,
    };

    for (QPushButton* btn : buttons) {
        if (!btn) continue;
        btn->setProperty("originalGeometry", btn->geometry());
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->setFixedSize(btn->geometry().size());
        btn->setAttribute(Qt::WA_Hover, true);
        btn->setMouseTracking(true);
        btn->installEventFilter(this);
    }
}

bool employeemenu::eventFilter(QObject *obj, QEvent *event) {
    QPushButton *button = qobject_cast<QPushButton*>(obj);

    if (button) {
        if (event->type() == QEvent::Enter) {
            animateButton(button, true);
            return true;
        }
        else if (event->type() == QEvent::Leave) {
            animateButton(button, false);
            return true;
        }
    }

    return QDialog::eventFilter(obj, event);
}

void employeemenu::animateButton(QPushButton* button, bool scaleUp) {
    if (!button) return;

    QRect original = button->property("originalGeometry").toRect();
    QRect current = button->geometry();
    if (original.isNull()) original = current;

    QPropertyAnimation *animation = new QPropertyAnimation(button, "geometry");
    animation->setDuration(200);

    if (scaleUp) {
        int newWidth = int(original.width() * 1.1);
        int newHeight = int(original.height() * 1.1);
        int offsetX = (newWidth - original.width()) / 2;
        int offsetY = (newHeight - original.height()) / 2;

        QRect scaled(
            original.x() - offsetX,
            original.y() - offsetY,
            newWidth,
            newHeight
            );

        animation->setStartValue(current);
        animation->setEndValue(scaled);
        animation->setEasingCurve(QEasingCurve::OutCubic);
    } else {
        animation->setStartValue(current);
        animation->setEndValue(original);
        animation->setEasingCurve(QEasingCurve::InCubic);
    }

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

employeemenu::~employeemenu()
{
    delete ui;
}

void employeemenu::on_b5_clicked()
{
    this->parentWidget()->show();
    this->hide();
}


void employeemenu::on_b4_clicked()
{
    exit(1);
}


void employeemenu::on_b6_clicked()
{
    ac=new addcustomer (this);
    this->hide();
    ac->show();
}

void employeemenu::on_b3_clicked()
{
    secondwindow2 * sw=qobject_cast<secondwindow2*>(this->parentWidget());
    MainWindow * mw=qobject_cast<MainWindow*>(sw->parentWidget());
    customers &cs=mw->customers;
    for(int i=0;i < cs.ncust;i++){
        account a=cs.cust[i].acc;
        for(int j=0;j<=a.dailyTransactions.last;j++){
            saveTransactions(a.dailyTransactions.transactions[j],cs.cust[i]);
        }
        a.dailyTransactions.last = -1;
        a.dailyTransactions.lastUndoDate.clear();
        saveToCSVEdit(mw->customers, i);
    }
    rewritec(mw->customers);
    readArchieveTransactions(mw->arch);
    ui->l->setFont(QFont("Segoe UI", 14, QFont::Bold));
    ui->l->setText("Day ended successfully");
}

void employeemenu::on_b7_clicked()
{
    lc=new listaccount(this);
    this->hide();
    lc->show();
}


void employeemenu::on_b9_clicked()
{
    dl=new displayloans(this);
    this->hide();
    dl->show();
}


void employeemenu::on_b2_clicked()
{
    ml=new manageloans(this);
    this->hide();
    ml->show();
}

