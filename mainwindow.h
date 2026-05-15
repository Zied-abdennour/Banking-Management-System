#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow1.h"
#include "secondwindow2.h"
#include"customer.h"
#include"employee.h"
#include "secondwindow3.h"
#include <QPropertyAnimation>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    customers customers;
    employees employees;
    archieved arch;
    secondwindow1 *customerLoginPage;

private slots:
    void on_btnCustomer_clicked();

    void on_btnEmployee_clicked();

    void on_exit_clicked();

    void on_manager_clicked();

private:
    Ui::MainWindow *ui;
    void setupButtonAnimations();
    bool eventFilter(QObject *obj, QEvent *event) override;
    void animateButton(QPushButton* button, bool scaleUp);
    secondwindow3 * login;
    secondwindow2 *employeeLoginPage;
};
#endif
