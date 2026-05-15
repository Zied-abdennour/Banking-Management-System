#include "transactionmeth.h"
using namespace std;


void createTarray(TransactionArray& TA) {
    TA.last = -1;
}
bool isTarrayEmpty(const TransactionArray& TA) {
    return TA.last == -1;
}
int addTransaction(TransactionArray& TA, transaction t) {
    if (TA.last >= 99) {
        return 0;
    }
    TA.last++;
    TA.transactions[TA.last] = t;
    return 1;
}
bool removeLastTransaction(TransactionArray& TA, int last) {
    if (isTarrayEmpty(TA)) {
        return false;
    }
    else {
        TA.last--;
        return true;
    }
}
