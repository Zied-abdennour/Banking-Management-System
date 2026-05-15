#include "thirdwindow12.h"
#include "ui_thirdwindow12.h"
#include "money.h"
#include "dailytransaction.h"
#include "deposit.h"
#include "showloans.h"

thirdwindow12::thirdwindow12(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::thirdwindow12)
{
    ui->setupUi(this);
    setupButtonAnimations();
}

thirdwindow12::~thirdwindow12()
{
    delete ui;
}

void thirdwindow12::setupButtonAnimations() {
    QList<QPushButton*> buttons = {
        ui->btn1,
        ui->btn2,
        ui->btn4,
        ui->btn7,
        ui->btn3,
        ui->btn8
    };

    for (QPushButton* btn : buttons) {
        btn->installEventFilter(this);
        btn->setProperty("originalGeometry", btn->geometry());
    }
}

bool thirdwindow12::eventFilter(QObject *obj, QEvent *event) {
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

void thirdwindow12::animateButton(QPushButton* button, bool scaleUp) {
    QPropertyAnimation *animation = new QPropertyAnimation(button, "geometry");
    animation->setDuration(200);

    QRect original = button->property("originalGeometry").toRect();
    QRect current = button->geometry();

    if (scaleUp) {
        int newWidth = original.width() * 1.1;
        int newHeight = original.height() * 1.1;
        int offsetX = (newWidth - original.width()) / 2;
        int offsetY = (newHeight - original.height()) / 2;

        QRect scaled = QRect(
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

void thirdwindow12::on_btn1_clicked()
{
    hide();
    Money = new money(this);
    Money->show();
}

void thirdwindow12::on_btn3_clicked()
{
    hide();
    sl = new showloans(this);
    sl->show();
}

void thirdwindow12::on_btn2_clicked()
{
    hide();
    d = new deposit(this);
    d->show();
}

void thirdwindow12::on_btn4_clicked()
{
    hide();
    dt = new dailytransaction(this);
    dt->show();
}

void thirdwindow12::on_btn7_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

void thirdwindow12::on_btn8_clicked()
{
    exit(1);
}

