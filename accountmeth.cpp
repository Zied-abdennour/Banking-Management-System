#include "accountmeth.h"
#include "transactionmeth.h"
#include "loanmeth.h"
#include <QDateTime>
using namespace std;

void initAccount(account& acc) {
    acc.AccountNumber = "";
    acc.AccountType = 0;
    acc.IBAN = "TN59";
    acc.BranchCode = 0;
    acc.AccountHolderName = "";
    acc.OpeningDate = "";
    acc.Status = "Active";
    acc.Balance = 0.0;
    createTarray(acc.dailyTransactions);
    acc.l = createloanlist();
    acc.requestl = nullptr;
}
int Deposit(account& acc, int amount) {
    transaction t;
    t.TID = stoi(acc.AccountNumber.toStdString()) + acc.dailyTransactions.last+1;
    t.number = acc.AccountNumber;
    t.Type = "Deposit";
    t.Amount = amount;
    t.Date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    if (!(addTransaction(acc.dailyTransactions,t))){
        return 0;
    }
    acc.Balance += amount;
    return 1;
}
int withdraw(account& acc, int amount) {
    if (amount > acc.Balance) {
        return 0;
    }
    if (amount % 10 != 0) {
        return 1;
    }
    transaction t;
    t.TID = stoi(acc.AccountNumber.toStdString()) + acc.dailyTransactions.last+1;
    t.number = acc.AccountNumber;
    t.Type = "Withdrawal";
    t.Amount = amount;
    t.Date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    if (!(addTransaction(acc.dailyTransactions,t))){
        return 2;
    }
    acc.Balance -= amount;
    return 3;
}
bool undoLast(account& acc) {
    if (isTarrayEmpty(acc.dailyTransactions)) {
        return false;
    }
    transaction lastTransaction = acc.dailyTransactions.transactions[acc.dailyTransactions.last];
    if (lastTransaction.Type == "Deposit") {
        acc.Balance -= lastTransaction.Amount;
    }
    else if (lastTransaction.Type == "Withdrawal") {
        acc.Balance += lastTransaction.Amount;
    }
    return removeLastTransaction(acc.dailyTransactions, acc.dailyTransactions.last);
}
bool addrequestloan(employees& emp, rloan newLoan) {
    return radd(&emp.requestl, newLoan);
}
