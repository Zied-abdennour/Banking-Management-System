#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "data.h"
#include "datae.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    readdata(customers);
    readEmployeeData(employees, customers);
    readArchieveAccounts(arch);
    readArchieveLoans(arch);
    readArchieveTransactions(arch);

    setupButtonAnimations();

    ui->time->setEnabled(false);
    ui->time->setDateTime(QDateTime::currentDateTime());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupButtonAnimations() {
    QList<QPushButton*> buttons = {
        ui->btnCustomer,
        ui->btnEmployee,
        ui->manager,
        ui->exit
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

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
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

    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::animateButton(QPushButton* button, bool scaleUp) {
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

void MainWindow::on_btnCustomer_clicked()
{
    hide();
    customerLoginPage = new secondwindow1(this);
    customerLoginPage->show();
}

void MainWindow::on_btnEmployee_clicked()
{
    hide();
    employeeLoginPage = new secondwindow2(this);
    employeeLoginPage->show();
}

void MainWindow::on_exit_clicked()
{
    exit(1);
}

void MainWindow::on_manager_clicked()
{
    login = new secondwindow3(this);
    hide();
    login->show();
}
