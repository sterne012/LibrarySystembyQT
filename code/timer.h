#ifndef TIMER_H
#define TIMER_H
#include <cmath>
#include <QDateTime>

char IsLeapYear(int Year);
int GetMidMonthDays(int m1, int m2, int y);
int GetSameYearDays(int y1, int m1, int d1, int y2, int m2, int d2);
int GetMidYearDays(int y1, int y2);
int GetDifferentYearDays(int y1, int m1, int d1, int y2, int m2, int d2);
int Date(int year, int month, int day);
#endif // TIMER_H
