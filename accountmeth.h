#ifndef ACCOUNTMETH_H
#define ACCOUNTMETH_H
#include "account.h"
#include"employee.h"
using namespace std;

void initAccount(account& acc);
int Deposit(account& acc, int amount);
int withdraw(account& acc, int amount);
bool undoLast(account& acc);
bool addrequestloan(employees& emp, rloan newLoan);
#endif
