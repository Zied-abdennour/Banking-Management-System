#ifndef DISPLAYEMPLOYEE_H
#define DISPLAYEMPLOYEE_H

#include <QDialog>

namespace Ui {
class displayemployee;
}

class displayemployee : public QDialog
{
    Q_OBJECT

public:
    explicit displayemployee(QWidget *parent = nullptr);
    ~displayemployee();

private slots:
    void on_c_clicked();

    void on_back_2_clicked();

    void on_exit_2_clicked();

    void on_back_clicked();

private:
    Ui::displayemployee *ui;
};

#endif // DISPLAYEMPLOYEE_H
