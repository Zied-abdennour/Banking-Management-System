#ifndef LOAN_H
#define LOAN_H
#include <Qstring>
using namespace std;

struct loan {
    QString LoanID;
    QString LoanType;
    double PrincipalAmount;
    double InterestRate;
    double AmountPaid;
    double RemainingBalance;
    QString StartDate;
    QString EndDate;
    QString LoanStatus;
    double MonthlyPayment;
};
struct rloan {
    QString LoanType;
    double PrincipalAmount;
    float InterestRate;
    QString StartDate;
    QString EndDate;
    double MonthlyPayment;
};
#endif
