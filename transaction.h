#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <Qstring>
using namespace std;
struct transaction {
    int TID;
    QString number;
    QString Type;
    double Amount;
    QString Date;
};
struct TransactionArray {
    transaction transactions[100];
    QString lastUndoDate;
    int last;
};

#endif
