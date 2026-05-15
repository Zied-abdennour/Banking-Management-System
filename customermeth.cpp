#include "customermeth.h"
#include "accountmeth.h"
#include <QMessageBox>
#include <QWidget>
#include <QLabel>
#include <QDateTime>

using namespace std;

bool registerCustomer(customer customers[], int& count,QLabel* l,QString name,QString surname,QString address,QString phone_number,QString email,QString password,QString username,QString date) {
    int i=0;
    bool test=true;
    while (i<name.size() && test){
        test=(('A'<=name[i] && name[i]<='Z') || ('a'<=name[i]&& name[i]<='z') || name[i]==' ');
        i++;
    }
    if (!test){
        l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        l->setText("wrong name");
        return false;
    }
    i=0;
    test=true;
    while (i<surname.size() && test){
        test=(('A'<=surname[i] && surname[i]<='Z') || ('a'<=surname[i]&& surname[i]<='z') || surname[i]==' ');
        i++;
    }
    if (!test){
        l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        l->setText("wrong surname");
        return false;
    }
    i=0;
    test=(phone_number.size()==8);
    while (i<phone_number.size() && test){
        test= '0'<=phone_number[i] && phone_number[i]<='9';
        i++;
    }
    if (!test){
        l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        l->setText("wrong phone_number");
        return false;
    }
    if (!(email.endsWith("@gmail.com"))){
        l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        l->setText("wrong email . Email must contains '@gmail.com' ");
        return false;
    }
    else {
        QString ch1="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-";
        QString ch2=email.mid(0, email.size()-10);
        i=0;
        while (i<ch2.size() && ch1.contains(ch2[i]))
            i++;
        if (!(i>=ch2.size())){
            l->setText("Email must contain alphabetics or \n numbers or '-' or '_' only");
            return false;
        }
    }

    for (int i = 0; i < count; i++) {
        if (customers[i].username == username) {
            l->setFont(QFont("Segoe UI", 14, QFont::Bold));
            l->setText("Username already exists \n Registration failed.");
            return false;
        }
    }
    if (count >= 100) {
        l->setFont(QFont("Segoe UI", 14, QFont::Bold));
        l->setText("Database full  Cannot register more customers.");
        return false;
    }
    customers[count].name =name;
    customers[count].surname = surname;
    customers[count].address = address;
    customers[count].phone_number = phone_number;
    customers[count].email = email;
    customers[count].username = username;
    customers[count].password = password;
    initAccount(customers[count].acc);
    customers[count].acc.OpeningDate=date;
    count++;

    return true;
}

int loginCustomer(const customer customers[], int count, QString u, QString p,QLabel *label) {
    for (int i = 0; i < count; i++) {
        if (customers[i].username == u && customers[i].password == p) {
            label->setFont(QFont("Segoe UI", 14, QFont::Bold));
            label->setText("Login successful!");
            return i;
        }
    }
    label->setFont(QFont("Segoe UI", 14, QFont::Bold));
    label->setText("Invalid username or password!");
    return -1;
}
bool removeCustomer(customers &cs, int index)
{
    if (index < 0 || index >= cs.ncust)
        return false;

    for (int i = index; i < cs.ncust - 1; i++) {
        cs.cust[i] = cs.cust[i + 1];
    }

    cs.ncust--;

    return true;
}
QString bankBranch(QString code){
    QString ch;
    if(code == "Tunis")
        ch = "001";
    else if(code == "Tataouine")
        ch = "810";
    else if(code == "Ariana")
        ch = "010";
    else if(code == "Ben Arous")
        ch = "011";
    else if(code == "Bizerte")
        ch = "111";
    else if(code == "Jendouba")
        ch = "012";
    else if(code == "Kef")
        ch = "021";
    else if(code == "Manouba")
        ch = "013";
    else if(code == "Nabeul")
        ch = "210";
    else if(code == "Siliana")
        ch = "014";
    else if(code == "Sousse")
        ch = "112";
    else if(code == "Zaghouan")
        ch = "310";
    else if(code == "Beja")
        ch = "015";
    else if(code == "Kairouan")
        ch = "222";
    else if(code == "Kasserine")
        ch = "017";
    else if(code == "Mahdia")
        ch = "414";
    else if(code == "Monastir")
        ch = "323";
    else if(code == "Sidi Bouzid")
        ch = "070";
    else if(code == "Sfax")
        ch = "710";
    else if(code == "Gabes")
        ch = "056";
    else if(code == "Gafsa")
        ch = "065";
    else if(code == "Kebili")
        ch = "510";
    else if(code == "Medenine")
        ch = "910";
    else if(code == "Tozeur")
        ch = "555";
    return ch;

}
bool updateCus(const QString& accNum, const QString& newStatus,customers& cs,int &index)
{
    if (cs.ncust == 0) {
        return false;
    }



    for (int i = 0; i < cs.ncust; ++i) {
        if (cs.cust[i].acc.AccountNumber == accNum) {
            cs.cust[i].acc.Status= newStatus;
            index=i;
            return true;
        }
    }

    return false;
}
int accountIndx(const customers& cs, const QString &accountnumber)
{
    for (int i = 0; i < cs.ncust; ++i)
    {
        if (accountnumber == cs.cust[i].acc.AccountNumber) {
            return i;
        }
    }
    return -1;
}
