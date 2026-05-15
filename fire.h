#ifndef FIRE_H
#define FIRE_H

#include <QDialog>

namespace Ui {
class fire;
}
class managermenu;
class fire : public QDialog
{
    Q_OBJECT

public:
    explicit fire(QWidget *parent = nullptr);
    ~fire();

private slots:
    void on_back_clicked();

    void on_exit_clicked();

    void on_fire_2_clicked();

    void on_no_clicked();

    void on_yes_clicked();

private:
    Ui::fire *ui;
    managermenu *mm;
};

#endif
