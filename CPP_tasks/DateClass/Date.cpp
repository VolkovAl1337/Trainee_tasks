#include "Date.h"
#include <iostream>
#include <map>

std::map<int, int> Date::monthLenths = {
    {1, 31}, {3, 31}, {4, 30}, {5, 31},
    {6, 30}, {7, 31}, {8, 31}, {9, 30},
    {10, 31}, {11, 30}, {12, 31}
};

Date::Date()
{
    day = 1;
    month = 1;
    year = 1;
}

Date::Date(int day, int month, int year)
{
    if(isDateCorrect(day, month, year)) {
        this->year = year;
        this->month = month;
        this->day = day;
    } else {
        throw WrongDateException();
    }

}

Date::Date(const Date& d1)
{
    day = d1.day;
    month = d1.month;
    year = d1.year;
}

inline bool Date::isLeap(int year) const
{
    return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
}

bool Date::isDateCorrect(int day, int month, int year) const
{
    if (year == 0) {
        return false;
    }

    if (month > maxMonthNum) {
        return false;
    }

    if (month < 1) {
        return false;
    }

    if (day < 1) {
        return false;
    }

    if (month == febNum) {
        if (day == longFebDays) {
            if (!isLeap(year)) {
                return false;
            }
        }
        return true;
    }

    if (day > monthLenths[month]) {
        return false;
    }

    return true;
}

void Date::setDay(const int& day)
{
    if (isDateCorrect(day, this->month, this->year)) {
        this->day = day;
    } else {
        throw WrongDateException();
    }
}

void Date::setMonth(const int& month)
{
    if (isDateCorrect(this->day, month, this->year)) {
        this->month = month;
    } else {
        throw WrongDateException();
    }
}

void Date::setYear(const int& year)
{
    if (isDateCorrect(this->day, this->month, year)) {
        this->year = year;
    } else {
        throw WrongDateException();
    }
}

int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getMonthLength() const
{
    if (month == febNum) {
        if (isLeap(year)) {
            return longFebDays;
        } else {
            return shortFebDays;
        }
    }
    return (monthLenths[month]);
}

int Date::getYear() const
{
    return year;
}

void Date::addDays(int days)
{
    if (days > 0) {
        while (days + day > getMonthLength()) {
            days -= getMonthLength() - day + 1;
            day = 1;
            month += 1;

            if (month > maxMonthNum) {
                year += 1;

                if (year == 0) {
                    year = 1;
                }

                month = 1;
            }
        }
        day += days;
    } else {
        while (days + day < 1) {
            days += day;
            month -= 1;
            day = getMonthLength();

            if (month == 0) {
                year -= 1;

                if (year == 0) {
                    year = -1;
                }

                month = maxMonthNum;
            }
        }
        day += days;
    }
}

void Date::addMonths(int months)
{
    if (months > 0) {
        while (month + months > maxMonthNum) {
            months -= maxMonthNum - month + 1;
            year += 1;
            if (year == 0) {
                year = 1;
            }
        }

        month += months;

        if (month == febNum && day > shortFebDays) {
            if (isLeap(year)) {
                if (day > longFebDays) {
                    month = febNum + 1;
                    day = 1;
                }
            } else {
                month = febNum + 1;
                day = 1;
            }

        }
    } else {
        while (months + month < 1) {
            months += maxMonthNum;
            year -= 1;
            if (year == 0) {
                year = -1;
            }
        }

        month += months;

        if (month == febNum && day > shortFebDays) {
            day = getMonthLength();
        }
    }
}

void Date::addYears(int years)
{
    if (years > 0) {
        year += years;

        if (year == 0) {
            year = 1;
        }

        if (month == febNum && day > shortFebDays) {
            if (isLeap(year)) {
                if (day > longFebDays) {
                    month = febNum + 1;
                    day = 1;
                }
            } else {
                month = febNum + 1;
                day = 1;
            }
        }
    } else {
        year += years;
        if (year == 0) {
            year = -1;
        }
        if (month == febNum && day > shortFebDays) {
            day = getMonthLength();
        }
    }
}

void Date::subDays(int days)
{
    addDays(-days);
}

void Date::subMonths(int months)
{
    addMonths(-months);
}

void Date::subYears(int years)
{
    addYears(-years);
}

std::ostream& operator<<(std::ostream& os, const Date& dt)
{
    os << (dt.getDay() < decBase ? "0" : "");
    os << dt.getDay() << ".";
    os << (dt.getMonth() < decBase ? "0" : "");
    os << dt.getMonth() << "." << dt.getYear();
    return os;
}
