#include "datae.h"
#include "loanmeth.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <qapplication.h>

QString getEmployeesFilePath() {
    return QCoreApplication::applicationDirPath() + "/employees.csv";
}

QString getEmployeesTempFilePath() {
    return QCoreApplication::applicationDirPath() + "/employees_temp.csv";
}

QString getArchieveAccountsPath() {
    return QCoreApplication::applicationDirPath() + "/archieve_accounts.csv";
}

QString getArchieveTransactionsPath() {
    return QCoreApplication::applicationDirPath() + "/archieve_transactions.csv";
}

QString getArchieveLoansPath() {
    return QCoreApplication::applicationDirPath() + "/archieve_loans.csv";
}

void saveEmployeeToCSV(const employee &e)
{
    QFile file(getEmployeesFilePath());

    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);

        out << e.Id << ","
            << e.Name << ","
            << e.LastName << ","
            << e.Address << ","
            << e.Salary << ","
            << e.HireDate << ","
            << e.BankBranch << ","
            << e.username << ","
            << e.password << "\n";
    }
}

void rewrite(const employees &es) {
    QString tempPath = getEmployeesTempFilePath();
    QString filePath = getEmployeesFilePath();

    QFile temp(tempPath);
    if (!temp.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&temp);

    for(int i = 0; i < es.nemp; i++){
        const employee &e = es.employees[i];

        out << e.Id << ","
            << e.Name << ","
            << e.LastName << ","
            << e.Address << ","
            << e.Salary << ","
            << e.HireDate << ","
            << e.BankBranch << ","
            << e.username << ","
            << e.password << "\n";
    }

    temp.close();
    QFile::remove(filePath);
    QFile::rename(tempPath, filePath);
}

void saveEmployeeEdit(const employees &es, int index)
{
    QString filePath = getEmployeesFilePath();
    QString tempPath = getEmployeesTempFilePath();

    QFile file(filePath);
    QFile temp(tempPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    if (!temp.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    QTextStream out(&temp);

    int lineNum = 0;

    while (!in.atEnd())
    {
        QString line = in.readLine();

        if (lineNum == index)
        {
            const employee &e = es.employees[index];

            out << e.Id << ","
                << e.Name << ","
                << e.LastName << ","
                << e.Address << ","
                << e.Salary << ","
                << e.HireDate << ","
                << e.BankBranch << ","
                << e.username << ","
                << e.password << "\n";
        }
        else {
            out << line << "\n";
        }

        lineNum++;
    }

    file.close();
    temp.close();

    QFile::remove(filePath);
    QFile::rename(tempPath, filePath);
}


void readEmployeeData(employees &es, const customers &cs)
{
    QFile file(getEmployeesFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        es.nemp = 0;
        es.requestl = rList{nullptr, nullptr, 0};
        return;
    }

    QTextStream in(&file);
    int i = 0;

    while (!in.atEnd() && i < 100) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList f = line.split(",");
        if (f.size() < 9) continue;

        employee e;
        e.Id = f[0].toInt();
        e.Name = f[1];
        e.LastName = f[2];
        e.Address = f[3];
        e.Salary = f[4].toFloat();
        e.HireDate = f[5];
        e.BankBranch = f[6];
        e.username = f[7];
        e.password = f[8];

        es.employees[i++] = e;
    }

    es.nemp = i;
    es.requestl = rList{nullptr, nullptr, 0};

    for (int k = 0; k < cs.ncust; k++) {
        const customer &c = cs.cust[k];
        if (c.acc.requestl != nullptr) {
            radd(&es.requestl, *(c.acc.requestl));
        }
    }

    file.close();
}

void saveAccount(account c)
{
    QFile file(getArchieveAccountsPath());

    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << c.AccountNumber << ";"
        << c.AccountType << ";"
        << c.IBAN << ";"
        << c.BranchCode << ";"
        << c.AccountHolderName << ";"
        << c.OpeningDate << ";"
        << c.Status << ";"
        << c.Balance << "\n";
}

void saveTransactions(transaction t, customer c)
{
    QFile file(getArchieveTransactionsPath());

    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << c.username << ":"
        << t.TID << ":"
        << t.number << ":"
        << t.Type << ":"
        << t.Amount << ":"
        << t.Date << "\n";
}


void saveLoan(loan l)
{
    QFile file(getArchieveLoansPath());

    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << l.PrincipalAmount << "?"
        << l.InterestRate << "?"
        << l.StartDate << "?"
        << l.EndDate << "?"
        << l.LoanID << "?"
        << l.LoanStatus << "?"
        << l.LoanType << "?"
        << l.MonthlyPayment << "\n";
}

void readArchieveAccounts(archieved &arch)
{
    arch.nacc = 0;

    QString path = QCoreApplication::applicationDirPath() + "/archieve_accounts.csv";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    int index = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList f = line.split(";");
        if (f.size() < 8) continue;

        arch.archivedacc[index].AccountNumber     = f[0];
        arch.archivedacc[index].AccountType       = f[1];
        arch.archivedacc[index].IBAN              = f[2];
        arch.archivedacc[index].BranchCode        = f[3];
        arch.archivedacc[index].AccountHolderName = f[4];
        arch.archivedacc[index].OpeningDate       = f[5];
        arch.archivedacc[index].Status            = f[6];
        arch.archivedacc[index].Balance           = f[7].toDouble();

        index++;
    }

    arch.nacc = index;
    file.close();
}




void readArchieveLoans(archieved &arch)
{
    arch.completed_loans.head = nullptr;
    arch.completed_loans.size = 0;

    QString path = QCoreApplication::applicationDirPath() + "/archieve_loans.csv";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList p = line.split("?");
        if (p.size() < 8) continue;

        loan l;
        l.PrincipalAmount   = p[0].toDouble();
        l.InterestRate      = p[1].toFloat();
        l.StartDate         = p[2];
        l.EndDate           = p[3];
        l.LoanID            = p[4];
        l.LoanStatus        = p[5];
        l.LoanType          = p[6];
        l.MonthlyPayment    = p[7].toDouble();

        l.AmountPaid        = 0.0;
        l.RemainingBalance  = l.PrincipalAmount;

        addl(&arch.completed_loans, l);
    }

    file.close();
}


void readArchieveTransactions(archieved &arch)
{
    arch.transactions.head = nullptr;
    arch.transactions.size = 0;

    QString path = QCoreApplication::applicationDirPath() + "/archieve_transactions.csv";
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList p = line.split(":");
        if (p.size() < 6) continue;

        transaction t;
        t.TID    = p[1].toInt();
        t.number = p[2];
        t.Type   = p[3];
        t.Amount = p[4].toDouble();
        t.Date   = p[5];

        ADD(&arch.transactions, t, p[0]);
    }

    file.close();
}


void saveAllLoans(const lista &loans)
{
    QString path = QCoreApplication::applicationDirPath() + "/archieve_loans.csv";
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    node* current = loans.head;
    while (current != nullptr) {
        loan l = current->data;
        out << l.PrincipalAmount << "?"
            << l.InterestRate    << "?"
            << l.StartDate       << "?"
            << l.EndDate         << "?"
            << l.LoanID          << "?"
            << l.LoanStatus      << "?"
            << l.LoanType        << "?"
            << l.MonthlyPayment  << "\n";

        current = current->next;
    }

    file.close();
}

