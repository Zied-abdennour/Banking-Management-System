#ifndef AFTERREGISTERING_H
#define AFTERREGISTERING_H

#include <QDialog>

namespace Ui {
class afterregistering;
}

class afterregistering : public QDialog
{
    Q_OBJECT

public:
    explicit afterregistering(QWidget *parent = nullptr);
    ~afterregistering();

private slots:
    void on_finish_clicked();

    void on_back_clicked();

private:
    Ui::afterregistering *ui;
};

#endif // AFTERREGISTERING_H
