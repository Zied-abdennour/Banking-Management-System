#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QThread>
#include "data.h"
#include "loanmeth.h"
#include "transactionmeth.h"

QString getCustomersFilePath() {
    return QCoreApplication::applicationDirPath() + "/customers.csv";
}

QString getCustomersTempFilePath() {
    return QCoreApplication::applicationDirPath() + "/customers_temp.csv";
}

void saveToCSV1(customer c)
{
    QString filePath = getCustomersFilePath();
    QFile file(filePath);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);

        out << c.name << ","
            << c.surname << ","
            << c.phone_number << ","
            << c.address << ","
            << c.email << ","
            << c.username << ","
            << c.password << "&";

        out << c.acc.AccountNumber << ";"
            << c.acc.AccountType << ";"
            << c.acc.IBAN << ";"
            << c.acc.BranchCode << ";"
            << c.acc.AccountHolderName << ";"
            << c.acc.OpeningDate << ";"
            << c.acc.Status << ";"
            << c.acc.Balance << ";"
            << c.acc.dailyTransactions.last << ";"
            << c.acc.dailyTransactions.lastUndoDate;

        out << "&&&\n";
        file.close();
    }
}
void saveToCSVEdit(customers &cs, int index)
{
    QString filePath = getCustomersFilePath();
    QString tempPath = getCustomersTempFilePath();

    QFile file(filePath);
    QFile tempFile(tempPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.close();
        return;
    }

    QTextStream in(&file);
    QTextStream out(&tempFile);
    int currentLine = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (currentLine == index) {
            const customer &c = cs.cust[index];

            out << c.name << ","
                << c.surname << ","
                << c.phone_number << ","
                << c.address << ","
                << c.email << ","
                << c.username << ","
                << c.password << "&";

            out << c.acc.AccountNumber << ";"
                << c.acc.AccountType << ";"
                << c.acc.IBAN << ";"
                << c.acc.BranchCode << ";"
                << c.acc.AccountHolderName << ";"
                << c.acc.OpeningDate << ";"
                << c.acc.Status << ";"
                << c.acc.Balance << ";"
                << c.acc.dailyTransactions.last << ";"
                << c.acc.dailyTransactions.lastUndoDate <<"&";

            Node *currentLoan = c.acc.l.head;
            bool firstLoan = true;
            while (currentLoan != nullptr) {
                if (!firstLoan) out << ":";

                out << currentLoan->data.AmountPaid << "?"
                    << currentLoan->data.PrincipalAmount << "?"
                    << currentLoan->data.InterestRate << "?"
                    << currentLoan->data.RemainingBalance << "?"
                    << currentLoan->data.StartDate << "?"
                    << currentLoan->data.EndDate << "?"
                    << currentLoan->data.LoanID << "?"
                    << currentLoan->data.LoanStatus << "?"
                    << currentLoan->data.LoanType << "?"
                    << currentLoan->data.MonthlyPayment;

                firstLoan = false;
                currentLoan = currentLoan->next;
            }

            out << "&";

            if (c.acc.requestl != nullptr) {
                out << c.acc.requestl->PrincipalAmount << "!"
                    << c.acc.requestl->InterestRate << "!"
                    << c.acc.requestl->StartDate << "!"
                    << c.acc.requestl->EndDate << "!"
                    << c.acc.requestl->LoanType << "!"
                    << c.acc.requestl->MonthlyPayment;
            }
            out << "&";

            bool firstTransaction = true;
            for (int j = 0; j <= c.acc.dailyTransactions.last; j++) {
                if (!firstTransaction) out << "%";
                out << QString::number(c.acc.dailyTransactions.transactions[j].Amount) << "$"
                    << c.acc.dailyTransactions.transactions[j].Date << "$"
                    << QString::number(c.acc.dailyTransactions.transactions[j].TID) << "$"
                    << c.acc.dailyTransactions.transactions[j].Type << "$"
                    << c.acc.dailyTransactions.transactions[j].number;
                firstTransaction = false;
            }
            out << "\n";
        } else {
            out << line << "\n";
        }

        currentLine++;
    }

    out.flush();
    in.flush();
    file.close();
    tempFile.close();

    QThread::msleep(50);

    if (!QFile::remove(filePath)) {
        return;
    }

    QFile::rename(tempPath, filePath);
}

void readdata(customers &cs) {
    QString filePath = getCustomersFilePath();
    QFile file(filePath);

    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.close();
        }
        cs.ncust = 0;
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    int i = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.isEmpty()) continue;

        customer c;
        createTarray(c.acc.dailyTransactions);
        c.acc.l = createloanlist();

        QStringList sections = line.split("&");

        if (sections.size() < 5) {
            continue;
        }

        QStringList info = sections[0].split(",");
        if (info.size() >= 7) {
            c.name = info[0];
            c.surname = info[1];
            c.phone_number = info[2];
            c.address = info[3];
            c.email = info[4];
            c.username = info[5];
            c.password = info[6];
        } else {
            continue;
        }

        QStringList accFields = sections[1].split(";");
        if (accFields.size() > 9) {
            c.acc.AccountNumber = accFields[0];
            c.acc.AccountType = accFields[1];
            c.acc.IBAN = accFields[2];
            c.acc.BranchCode = accFields[3];
            c.acc.AccountHolderName = accFields[4];
            c.acc.OpeningDate = accFields[5];
            c.acc.Status = accFields[6];
            c.acc.Balance = accFields[7].toDouble();
            c.acc.dailyTransactions.last = accFields[8].toInt();
            c.acc.dailyTransactions.lastUndoDate = accFields[9];
        } else {
            c.acc.dailyTransactions.lastUndoDate = "";
            continue;
        }

        if (!sections[2].isEmpty()) {
            QStringList loans = sections[2].split(":");
            for (const QString &loanStr : std::as_const(loans)) {
                if (loanStr.isEmpty()) continue;
                QStringList parts = loanStr.split("?");
                if (parts.size() < 10) continue;

                loan ln;
                ln.AmountPaid = parts[0].toDouble();
                ln.PrincipalAmount = parts[1].toDouble();
                ln.InterestRate = parts[2].toFloat();
                ln.RemainingBalance = parts[3].toDouble();
                ln.StartDate = parts[4];
                ln.EndDate = parts[5];
                ln.LoanID = parts[6];
                ln.LoanStatus = parts[7];
                ln.LoanType = parts[8];
                ln.MonthlyPayment = parts[9].toDouble();
                addLoan(&c.acc.l, ln);
            }
        }

        if (sections.size() > 3 && !sections[3].isEmpty()) {
            QStringList req = sections[3].split("!");
            if (req.size() >= 6) {
                c.acc.requestl = new rloan();
                c.acc.requestl->PrincipalAmount = req[0].toDouble();
                c.acc.requestl->InterestRate = req[1].toFloat();
                c.acc.requestl->StartDate = req[2];
                c.acc.requestl->EndDate = req[3];
                c.acc.requestl->LoanType = req[4];
                c.acc.requestl->MonthlyPayment = req[5].toDouble();
            }
        } else {
            c.acc.requestl = nullptr;
        }

        if (sections.size() > 4 && !sections[4].isEmpty()) {
            QStringList t = sections[4].split("%");
            int ti = 0;
            for (const QString &trStr : std::as_const(t)) {
                if (trStr.isEmpty()) continue;
                QStringList part = trStr.split("$");
                if (part.size() >= 5) {
                    c.acc.dailyTransactions.transactions[ti].Amount = part[0].toDouble();
                    c.acc.dailyTransactions.transactions[ti].Date = part[1];
                    c.acc.dailyTransactions.transactions[ti].TID = part[2].toInt();
                    c.acc.dailyTransactions.transactions[ti].Type = part[3];
                    c.acc.dailyTransactions.transactions[ti].number = part[4];
                    ti++;
                }
            }
            c.acc.dailyTransactions.last = ti - 1;
        } else {
            c.acc.dailyTransactions.last = -1;
        }

        cs.cust[i] = c;
        i++;
    }

    cs.ncust = i;
    file.close();
}
void rewritec(const customers &cs) {
    QFile temp("customers_temp.csv");
    if (!temp.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&temp);

    for (int i = 0; i < cs.ncust; i++) {
        const customer &c = cs.cust[i];
        const account &a = c.acc;

        out << c.name << ","
            << c.surname << ","
            << c.phone_number << ","
            << c.address << ","
            << c.email << ","
            << c.username << ","
            << c.password << "&";


        out << a.AccountNumber << ";"
            << a.AccountType << ";"
            << a.IBAN << ";"
            << a.BranchCode << ";"
            << a.AccountHolderName << ";"
            << a.OpeningDate << ";"
            << a.Status << ";"
            << a.Balance << ";"
            << c.acc.dailyTransactions.last << ";"
            << c.acc.dailyTransactions.lastUndoDate <<"&";


        const Node* lnode = (a.l.head != nullptr) ? a.l.head : nullptr;
        bool firstLoan = true;
        while (lnode != nullptr) {
            const loan &ln = lnode->data;
            if (!firstLoan) out << ":";
            out << ln.AmountPaid << "?"
                << ln.PrincipalAmount << "?"
                << ln.InterestRate << "?"
                << ln.RemainingBalance << "?"
                << ln.StartDate << "?"
                << ln.EndDate << "?"
                << ln.LoanID << "?"
                << ln.LoanStatus << "?"
                << ln.LoanType << "?"
                << ln.MonthlyPayment;
            firstLoan = false;
            lnode = lnode->next;
        }
        out << "&";

        if (a.requestl != nullptr) {
            out << a.requestl->PrincipalAmount << "!"
                << a.requestl->InterestRate << "!"
                << a.requestl->StartDate << "!"
                << a.requestl->EndDate << "!"
                << a.requestl->LoanType << "!"
                << a.requestl->MonthlyPayment;
        }
        out << "&";

        for (int j = 0; j <= a.dailyTransactions.last; j++) {
            if (j != 0) out << "%";
            const transaction &tr = a.dailyTransactions.transactions[j];
            out << tr.Amount << "$"
                << tr.Date << "$"
                << tr.TID << "$"
                << tr.Type << "$"
                << tr.number;
        }

        out << "\n";
    }

    temp.close();

    QFile::remove("customers.csv");
    QFile::rename("customers_temp.csv", "customers.csv");
}
