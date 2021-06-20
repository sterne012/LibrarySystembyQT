#include "timer.h"

char IsLeapYear(int Year)
{
    if ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int GetMidMonthDays(int m1, int m2, int y)
{
    int MonthDays[] = { 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 };
    int i;
    int ds;
    ds = 0;
    for (i = m1 + 1; i < m2; i++)
    {
        ds += MonthDays[i - 1];
        if (i == 2)
        {
            if (IsLeapYear(y))
            {
                ds++;
            }
        }
    }
    return ds;
}
int GetSameYearDays(int y1, int m1, int d1, int y2, int m2, int d2)
{
    int MonthDays[] = { 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 };
    int Days;
    //如果月份相同
    if (m1 == m2)
    {
        Days = abs(d2 - d1);
    }
    else
    {
        //计算第一个月份的天数
        Days = abs(MonthDays[m1 - 1] - d1);
        if (m1 == 2)
        {
            if (IsLeapYear(y1))
            {
                Days++;
            }
        }
        if ((m1 + 1) != m2)
        {
            //计算中间月份的天数
            Days += GetMidMonthDays(m1, m2, y1);
        }
        Days += d2;
    }
    return Days;
}
int GetMidYearDays(int y1, int y2)
{
    int days = 0;
    int i = 0;
    for (i = y1 + 1; i < y2; i++)
    {
        if (IsLeapYear(i - 1))
        {
            days += 366;
        }
        else
            days += 365;
    }
    return days;
}
int GetDifferentYearDays(int y1, int m1, int d1, int y2, int m2, int d2)
{
    int MonthDays[] = { 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 };
    int days;
    if (y1 == y2)
    {
        days = GetSameYearDays(y1, m1, d1, y2, m2, d2);
    }
    else
    {
        days = MonthDays[m1 + 1] - d1;
        if ((y1 + 1) != y2)
        {
            days += GetMidYearDays(y1, y2);
        }
        days += GetMidMonthDays(m1 - 1, 13, y1);
        if (m2 == 1)
        {
            days += d2;
        }
        else
        {
            days += GetMidMonthDays(1, m2, y2);
            days += d2;
        }
    }
    return days;
}
int Date(int Year1, int Month1, int Day1)
{
    QDate current_date =QDate::currentDate();
    int year=current_date.year();
    int month=current_date.month();
    int day=current_date.day();
    int Days;
    Days = GetDifferentYearDays(Year1, Month1, Day1, year, month, day);
    return Days;
}
