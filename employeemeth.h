#ifndef EMPLOYEEMETH_H
#define EMPLOYEEMETH_H
#include<Qstring>
#include<Qlabel>
#include"employee.h"

bool loginEmployee(const employee employees[], int count, QString u, QString p, QLabel *label);
bool addEmployee(employees &tem,employee e);
void fireEmployee(employees &tem, QString id, QLabel *label);
bool modifyEmployee(employee &e,QString onwhat,QString New);
void sortEmployeesByLastName(employees &tem);
void sortEmployeesByBranch(employees &tem);
void sortEmployeeBylastRecruited(employees &tem);
#endif
