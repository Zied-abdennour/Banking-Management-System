#ifndef THIRDWINDOW11_H
#define THIRDWINDOW11_H

#include <QDialog>
#include"afterregistering.h"
namespace Ui {
class thirdwindow11;
}

class thirdwindow11 : public QDialog
{
    Q_OBJECT

public:
    explicit thirdwindow11(QWidget *parent = nullptr);
    ~thirdwindow11();
    QString date;
    int x;

private slots:
    void on_btnback_clicked();

    void on_btncreate_clicked();

private:
    Ui::thirdwindow11 *ui;
    afterregistering *afterregist;
};

#endif

