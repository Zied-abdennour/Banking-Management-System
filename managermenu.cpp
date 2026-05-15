#include "managermenu.h"
#include "ui_managermenu.h"

managermenu::managermenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::managermenu)
{
    ui->setupUi(this);
    setupButtonAnimations();
}

managermenu::~managermenu()
{
    delete ui;
}

void managermenu::setupButtonAnimations() {
    QList<QPushButton*> buttons = {
        ui->add,
        ui->arc,
        ui->back,
        ui->display,
        ui->exit,
        ui->fire,
        ui->modify,
        ui->stats
    };

    for (QPushButton* btn : buttons) {
        if (!btn) continue;
        btn->setProperty("originalGeometry", btn->geometry());
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btn->setFixedSize(btn->geometry().size());
        btn->setAttribute(Qt::WA_Hover, true);
        btn->setMouseTracking(true);
        btn->installEventFilter(this);
    }
}

bool managermenu::eventFilter(QObject *obj, QEvent *event) {
    QPushButton *button = qobject_cast<QPushButton*>(obj);

    if (button) {
        if (event->type() == QEvent::Enter) {
            animateButton(button, true);
            return true;
        }
        else if (event->type() == QEvent::Leave) {
            animateButton(button, false);
            return true;
        }
    }

    return QDialog::eventFilter(obj, event);
}

void managermenu::animateButton(QPushButton* button, bool scaleUp) {
    if (!button) return;

    QRect original = button->property("originalGeometry").toRect();
    QRect current = button->geometry();
    if (original.isNull()) original = current;

    QPropertyAnimation *animation = new QPropertyAnimation(button, "geometry");
    animation->setDuration(200);

    if (scaleUp) {
        int newWidth = int(original.width() * 1.1);
        int newHeight = int(original.height() * 1.1);
        int offsetX = (newWidth - original.width()) / 2;
        int offsetY = (newHeight - original.height()) / 2;

        QRect scaled(
            original.x() - offsetX,
            original.y() - offsetY,
            newWidth,
            newHeight
            );

        animation->setStartValue(current);
        animation->setEndValue(scaled);
        animation->setEasingCurve(QEasingCurve::OutCubic);
    } else {
        animation->setStartValue(current);
        animation->setEndValue(original);
        animation->setEasingCurve(QEasingCurve::InCubic);
    }

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void managermenu::on_add_clicked()
{
    a = new add(this);
    hide();
    a->show();
}

void managermenu::on_fire_clicked()
{
    f = new fire(this);
    hide();
    f->show();
}

void managermenu::on_stats_clicked()
{
    s = new stats(this);
    hide();
    s->show();
}

void managermenu::on_back_clicked()
{
    parentWidget()->show();
    hide();
}

void managermenu::on_exit_clicked()
{
    exit(1);
}

void managermenu::on_modify_clicked()
{
    m = new modify(this);
    hide();
    m->show();
}

void managermenu::on_display_clicked()
{
    d = new displayemployee(this);
    hide();
    d->show();
}

void managermenu::on_arc_clicked()
{
    archieve = new class archieve(this);
    hide();
    archieve->show();
}


