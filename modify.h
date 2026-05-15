#ifndef MODIFY_H
#define MODIFY_H

#include <QDialog>

namespace Ui {
class modify;
}

class modify : public QDialog
{
    Q_OBJECT

public:
    explicit modify(QWidget *parent = nullptr);
    ~modify();

private slots:
    void on_confirm_clicked();

    void on_back_clicked();

    void on_finish_clicked();

    void on_exit_clicked();

private:
    Ui::modify *ui;
    QString onwhat ;
    int id;
};

#endif // MODIFY_H
