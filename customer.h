#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "account.h"
#include<Qstring>
using namespace std;
struct customer {
    QString name;
    QString surname;
    QString address;
    QString phone_number;
    QString email;
    QString password;
    QString username;
    account acc;
};
struct customers{
    customer cust[100];
    int ncust = 0;
};
#endif
