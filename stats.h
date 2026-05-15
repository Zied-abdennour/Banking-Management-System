#ifndef STATS_H
#define STATS_H
#include "customer.h"
#include "employee.h"

#include <QDialog>

namespace Ui {
class stats;
}

class stats : public QDialog
{
    Q_OBJECT

public:
    explicit stats(QWidget *parent = nullptr);
    ~stats();

private slots:

    void on_c1_clicked();

    void on_c3_clicked();

    void on_c2_clicked();

    void on_back_clicked();

    void on_c4_clicked();

private:
    Ui::stats *ui;
    customers cs;
    employees es;
};

#endif // STATS_H
