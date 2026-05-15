#ifndef MANAGERMENU_H
#define MANAGERMENU_H

#include <QDialog>
#include "archieve.h"
#include "displayemployee.h"
#include"modify.h"
#include"fire.h"
#include"add.h"
#include"stats.h"
#include <QPropertyAnimation>
#include <QEvent>


namespace Ui {
class managermenu;
}

class managermenu : public QDialog
{
    Q_OBJECT

public:
    explicit managermenu(QWidget *parent = nullptr);
    ~managermenu();

private slots:
    void on_add_clicked();

    void on_modify_clicked();

    void on_fire_clicked();

    void on_stats_clicked();

    void on_back_clicked();

    void on_exit_clicked();

    void on_display_clicked();

    void on_arc_clicked();

private:
    Ui::managermenu *ui;
    stats * s;
    modify * m;
    fire * f;
    add * a;
    displayemployee *d;
    archieve *archieve;
    void setupButtonAnimations();
    bool eventFilter(QObject *obj, QEvent *event) override;
    void animateButton(QPushButton* button, bool scaleUp);
};

#endif
