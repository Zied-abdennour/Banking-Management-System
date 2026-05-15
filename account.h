#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "loanlist.h"
#include "transaction.h"
using namespace std;

struct account {
    QString AccountNumber;
    QString AccountType;
    QString IBAN;
    QString BranchCode;
    QString AccountHolderName;
    QString OpeningDate;
    QString Status;
    double Balance;
    List l;
    rloan *requestl;
    TransactionArray dailyTransactions;

};
#endif
