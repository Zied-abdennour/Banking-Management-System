#include "loanmeth.h"
#include "customer.h"
using namespace std;

int getTotalLoans(customer customers[], int count) {
    int totalLoans = 0;
    for (int i = 0; i < count; i++) {
        totalLoans += listSize(customers[i].acc.l);
    }
    return totalLoans;
}
int countLoansByType(customer customers[], int count, QString type) {
    int loanCount = 0;
    for (int i = 0; i < count; i++) {
        Node* current = customers[i].acc.l.head;
        while (current) {
            if (current->data.LoanType == type) {
                loanCount++;
            }
            current = current->next;
        }
    }
    return loanCount;
}
int countLoansByStatus(customer customers[], int count, QString status) {
    int loanCount = 0;
    for (int i = 0; i < count; i++) {
        Node* current = customers[i].acc.l.head;
        while (current) {
            if (current->data.LoanStatus == status) {
                loanCount++;
            }
            current = current->next;
        }
    }
    return loanCount;
}
int activeLoansByDate(customer customers[], int count, QString startDate, QString endDate) {
    int loanCount = 0;
    for (int i = 0; i < count; i++) {
        Node* current = customers[i].acc.l.head;
        while (current) {
            if (current->data.LoanStatus == "Active" &&
                current->data.StartDate >= startDate &&
                current->data.EndDate <= endDate) {
                loanCount++;
            }
            current = current->next;
        }
    }
    return loanCount;
}
int getCustomerWithMostLoans(customer customers[], int count) {
    int maxLoans = 0;
    int customerIndex = -1;
    for (int i = 0; i < count; i++) {
        int loanCount = listSize(customers[i].acc.l);
        if (loanCount > maxLoans) {
            maxLoans = loanCount;
            customerIndex = i;
        }
    }
    return customerIndex;
}
int getCustomerWithHighestBalance(customer customers[], int count) {
    int maxBalance = -1;
    int customerIndex = -1;
    for (int i = 0; i < count; i++) {
        if (customers[i].acc.Balance > maxBalance) {
            maxBalance = customers[i].acc.Balance;
            customerIndex = i;
        }
    }
    return customerIndex;
}
int getCustomerWithLowestBalance(customer customers[], int count) {
    int minBalance = customers[0].acc.Balance;
    int customerIndex = -1;
    for (int i = 1; i < count; i++) {
        if (customers[i].acc.Balance < minBalance) {
            minBalance = customers[i].acc.Balance;
            customerIndex = i;
        }
    }
    return customerIndex;
}
