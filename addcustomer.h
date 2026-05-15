#ifndef ADDCUSTOMER_H
#define ADDCUSTOMER_H

#include <QDialog>

namespace Ui {
class addcustomer;
}

class addcustomer : public QDialog
{
    Q_OBJECT

public:
    explicit addcustomer(QWidget *parent = nullptr);
    ~addcustomer();
    QString date;

private slots:
    void on_btncreate_2_clicked();

    void on_finish_clicked();

    void on_btnback_2_clicked();

    void on_back_clicked();

    void on_b2_clicked();

private:
    Ui::addcustomer *ui;
};

#endif // ADDCUSTOMER_H
