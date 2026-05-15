#ifndef DATA_H
#define DATA_H
#include "customer.h"

void readdata(customers &cs);
void saveToCSV1(customer c);
void saveToCSVEdit(customers &cs, int index);
void rewritec(const customers &cs);

#endif
