#ifndef MANAGELOANS_H
#define MANAGELOANS_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class manageloans;
}

class manageloans : public QDialog
{
    Q_OBJECT

public:
    explicit manageloans(QWidget *parent = nullptr);
    ~manageloans();

private slots:
    void on_tableWidget_cellActivated(int row, int column);

    void on_c_clicked();

    void on_c1_clicked();

    void on_back_clicked();

    void on_exit_clicked();

private:
    Ui::manageloans *ui;
    MainWindow *mw;
    secondwindow2 *sw;
    void loadr();
};

#endif // MANAGELOANS_H
