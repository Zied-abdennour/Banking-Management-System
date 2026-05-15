#ifndef STATISTICS_METH_H
#define STATISTICS_METH_H

#include "customer.h"
int getTotalLoans(customer customers[], int count);
int countLoansByType(customer customers[], int count, QString type);
int countLoansByStatus(customer customers[], int count, QString status);
int activeLoansByDate(customer customers[], int count, QString startDate, QString endDate);
int getCustomerWithMostLoans(customer customers[], int count);
int getCustomerWithHighestBalance(customer customers[], int count);
int getCustomerWithLowestBalance(customer customers[], int count);
#endif
