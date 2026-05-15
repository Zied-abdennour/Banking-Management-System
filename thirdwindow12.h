#ifndef THIRDWINDOW12_H
#define THIRDWINDOW12_H
#include <QPropertyAnimation>
#include <QEvent>

#include <QDialog>
namespace Ui {
class thirdwindow12;
}

class deposit;
class money;
class dailytransaction;
class showloans;

class thirdwindow12 : public QDialog
{
    Q_OBJECT

public:
    explicit thirdwindow12(QWidget *parent = nullptr);
    ~thirdwindow12();

private slots:
    void on_btn1_clicked();

    void on_btn3_clicked();

    void on_btn2_clicked();

    void on_btn4_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

private:
    Ui::thirdwindow12 *ui;
    deposit * d;
    money* Money;
    dailytransaction *dt;
    showloans *sl;
    void setupButtonAnimations();
    bool eventFilter(QObject *obj, QEvent *event) override;
    void animateButton(QPushButton* button, bool scaleUp);
};

#endif
