#include "functions.h"
#include <QString>
#include <cctype>
#include <QChar>
#include <cctype>

using namespace std;

bool isValidDat(const QString& d)
{
    if (d.length() != 10)
        return false;


    if (d[4] != '-' || d[7] != '-')
        return false;
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7)
        {
            if (!d[i].isDigit())
                return false;
        }
    }
    QStringView v(d);
    int year = (v.mid(0, 4)).toInt();
    int month = (v.mid(5, 2)).toInt();
    int day = (v.mid(8, 2)).toInt();

    if (month < 1 || month > 12)
        return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (leap && month == 2)
        return (day >= 1 && day <= 29);

    return (day >= 1 && day <= daysInMonth[month - 1]);
}
bool isAlpha(const QString& ch)
{
    if (ch.isEmpty())
        return false;

    for (int i = 0; i < ch.length(); ++i)
    {
        QChar c = ch[i];


        if (!c.isLetter() && c != ' ')
            return false;
    }

    return true;
}


bool isDigital(const QString& ch)
{
    if (ch=="")
        return false;

    for (int i=0 ; i<ch.length();i++) {
        if (!ch[i].isDigit()) {
            return false;
        }
    }
    return true;
}
