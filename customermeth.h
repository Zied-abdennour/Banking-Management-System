#ifndef CUSTOMERMETH_H
#define CUSTOMERMETH_H
#include "customer.h"
#include <QMessageBox>
using namespace std;

bool registerCustomer(customer customers[], int& count, QLabel* l, QString name, QString surname, QString address, QString phone_number, QString email, QString password, QString username,QString date);
int loginCustomer(const customer costumers[], int count, QString u, QString p,QLabel *label);
bool removeCustomer(customers &cs, int index);
QString bankBranch(QString ch);
bool updateCus(const QString& accNum, const QString& newStatus,customers& cs,int &index);
int accountIndx(const customers& cs, const QString &accountnumber);
#endif
