#include "employeemeth.h"
#include "datae.h"


bool loginEmployee(const employee employees[], int count, QString u, QString p, QLabel *label)
{
    for (int i = 0; i < count; i++) {
        if (employees[i].username == u && employees[i].password == p) {
            return true;
        }
    }
    label->setFont(QFont("Segoe UI", 14, QFont::Bold));
    label->setText("Incorrect username or password");
    return false;
}
bool addEmployee(employees &tem, employee e)
{
    if (tem.nemp >= 100)
        return false;

    tem.employees[tem.nemp] = e;
    tem.nemp++;
    return true;
}
void fireEmployee(employees &tem, QString id, QLabel *label)
{
    if (id.isEmpty()) {
        label->setStyleSheet("color: rgb(170,0,0);");
        label->setFont(QFont("Segoe UI", 14, QFont::Bold));
        label->setText("Please enter an employee ID!");
        return;
    }

    int index = -1;
    int employeeId = id.toInt();

    for (int i = 0; i < tem.nemp; i++) {
        if (employeeId == tem.employees[i].Id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        label->setFont(QFont("Segoe UI", 14, QFont::Bold));
        label->setStyleSheet("color: rgb(170,0,0);");
        label->setText("Employee not found!");
        return;
    }
    for (int i = index; i < tem.nemp - 1; i++) {
        tem.employees[i] = tem.employees[i + 1];
    }
    tem.nemp--;
    rewrite(tem);
    label->setFont(QFont("Segoe UI", 14, QFont::Bold));
    label->setStyleSheet("color: rgb(85, 170, 127);");
    label->setText("Employee removed successfully!");
}
bool modifyEmployee(employee &e, QString onwhat, QString New)
{
    bool ok=true;
    if (onwhat == "Name")            e.Name = New;
    else if (onwhat == "Last Name")  e.LastName = New;
    else if (onwhat == "Address")    e.Address = New;
    else if (onwhat == "Salary")     e.Salary = New.toDouble(&ok);
    else if (onwhat == "Id")         e.Id = New.toInt(&ok);
    else if (onwhat == "Bank Branch")e.BankBranch = New;
    else
        return false;

    return ok;
}
void sortEmployeesByLastName(employees &tem){
    if (tem.nemp <= 1) {
        return;
    }
    for (int i = 0; i < tem.nemp - 1; ++i) {
        for (int j = 0; j < tem.nemp - 1 - i; ++j) {

            if (tem.employees[j].LastName > tem.employees[j + 1].LastName) {

                employee temp = tem.employees[j];
                tem.employees[j] = tem.employees[j + 1];
                tem.employees[j + 1] = temp;
            }
        }
    }
}
void sortEmployeesByBranch(employees &tem){
    if (tem.nemp <= 1) {
        return;
    }

    for (int i = 0; i < tem.nemp - 1; ++i) {
        for (int j = 0; j < tem.nemp - 1 - i; ++j) {

            if (tem.employees[j].BankBranch > tem.employees[j + 1].BankBranch) {
                employee temp = tem.employees[j];
                tem.employees[j] = tem.employees[j + 1];
                tem.employees[j + 1] = temp;
            }
        }
    }
}
void sortEmployeeBylastRecruited(employees &tem){
    if (tem.nemp <= 1) {
        return;
    }

    for (int i = 0; i < tem.nemp - 1; ++i) {
        for (int j = 0; j < tem.nemp - 1 - i; ++j) {
            if (tem.employees[j].HireDate < tem.employees[j + 1].HireDate) {
                employee temp = tem.employees[j];
                tem.employees[j] = tem.employees[j + 1];
                tem.employees[j + 1] = temp;
            }
        }
    }
}
