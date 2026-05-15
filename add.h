#ifndef ADD_H
#define ADD_H

#include <QDialog>

namespace Ui {
class add;
}

class add : public QDialog
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = nullptr);
    ~add();

private slots:
    void on_exit_clicked();

    void on_Add_clicked();

    void on_back_clicked();

private:
    Ui::add *ui;
};

#endif
