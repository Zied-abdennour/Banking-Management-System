#ifndef TRANSACTIONMETH_H
#define TRANSACTIONMETH_H
#include "transaction.h"
using namespace std;

void createTarray(TransactionArray& TA);
bool isTarrayEmpty(const TransactionArray& TA);
int addTransaction(TransactionArray& TA, transaction t);
bool removeLastTransaction(TransactionArray& TA, int last);

#endif
