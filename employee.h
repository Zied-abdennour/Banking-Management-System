#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "account.h"
#include"loanlist.h"
#include<Qstring>
using namespace std;

struct employee {
    int Id;
    QString Name;
    QString	LastName;
    QString Address;
    float Salary;
    QString HireDate;
    QString BankBranch;
    QString username;
    QString password;
};
struct employees{
    employee employees[100];
    int nemp=0;
    rList requestl;
};
struct archieved{
    account archivedacc[100];
    int nacc=0;
    lista completed_loans;
    LIST transactions;
};

#endif
