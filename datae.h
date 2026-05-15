#ifndef DATAE_H
#define DATAE_H

#include "customer.h"
#include "employee.h"
void saveEmployeeToCSV(const employee &e);
void saveEmployeeEdit(const employees &es, int index);
void readEmployeeData(employees &es, const customers &cs);

void rewrite(const employees &es);
void saveAccount(account c);
void saveLoan(loan l);
void readArchieveAccounts(archieved &arch);
void readArchieveLoans(archieved &arch);
void saveTransactions(transaction t, customer c);
void readArchieveTransactions(archieved &arch);
void saveAllLoans(const lista &loans);
#endif
