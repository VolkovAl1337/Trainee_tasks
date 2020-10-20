#include "DateClass.h"
#include <iostream>

Date::Date() = default;

Date::Date(int day, int month, int year)
{
    dayMonthCheck(day, month, year);
    this->year = year;
    this->month = month;
    this->day = day;
}

Date::Date(const Date& d1)
{
    day = d1.day;
    month = d1.month;
    year = d1.year;
}

void Date::dayMonthCheck(int day, int month, int year)
{
    if (month > 12) {
        throw TooBigMonthException();
    }
    if (month < 1) {
        throw TooSmallMonthException();
    }

    if (day < 1) {
        throw TooSmallDayException();
    }

    switch (month)
    {
    case 1:
        if (day > 31) {
            throw TooBigDayException();
        }
        break;

    case 2:
        if (day > 29) {
            throw TooBigDayException();
        }
        if (day == 29) {
            if (!((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))) {
                throw TooBigDayException();
            }
        }
        break;

    case 3:
        if (day > 31) {
            throw TooBigDayException();
        }
        break;

    case 4:
        if (day > 30) {
            throw TooBigDayException();
        }
        break;

    case 5:
        if (day > 31) {
            throw TooBigDayException();
        }
        break;

    case 6:
        if (day > 30) {
            throw TooBigDayException();
        }
        break;

    case 7:
        if (day > 31) {
            throw TooBigDayException();
        }
        break;

    case 8:
        if (day > 31) {
            throw TooBigDayException();
        }
        break;

    case 9:
        if (day > 30) {
            throw TooBigDayException();
        }
        break;

    case 10:
        if (day > 31) {
            throw TooBigDayException();
        }
        break;

    case 11:
        if (day > 30) {
            throw TooBigDayException();
        }
        break;

    case 12:
        if (day > 31) {
            throw TooBigDayException();
        }
        break;

    default:
        break;
    }
}

void Date::setDay(int day) {
    dayMonthCheck(day, this->month, this->year);
    this->day = day;
}

void Date::setMonth(int month) {
    dayMonthCheck(this->day, month, this->year);
    this->month = month;
}

void Date::setYear(int year) {
    dayMonthCheck(this->day, this->month, year);
    this->year = year;
}

int Date::getDay() {
    return day;
}

int Date::getMonth() {
    return month;
}

int Date::getYear() {
    return year;
}

Date& Date::operator ++() {
    try
    {
        dayMonthCheck(day + 1, month, year);
        day += 1;
    }
    catch(TooBigDayException)
    {
        try
        {
            dayMonthCheck(1, month + 1, year);
            month += 1;
            day = 1;
        }
        catch(TooBigMonthException)
        {
            year += 1;
            month = 1;
            day = 1;
        }
    }
}

Date& Date::operator--() {
    try
    {
        dayMonthCheck(day - 1, month, year);
        day -= 1;
    }
    catch(TooSmallDayException)
    {
        if (month == 1) {
            year -= 1;
            month = 12;
        } else {
            month -= 1;
        }
        switch (month)
        {
        case 1:
            day = 31;
            break;

        case 2:
            day = 28;

            if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)) {
                day = 29;
            }
            break;

        case 3:
            day = 31;
            break;

        case 4:
            day = 30;
            break;

        case 5:
            day = 31;
            break;

        case 6:
            day = 30;
            break;

        case 7:
            day = 31;
            break;

        case 8:
            day = 31;
            break;

        case 9:
            day = 30;
            break;

        case 10:
            day = 31;
            break;

        case 11:
            day = 30;
            break;

        case 12:
            day = 31;
            break;

        default:
            break;
        }
    }

}

void Date::print()
{
    std::cout << (day < 10 ? "0" : "");
    std::cout << day << ".";
    std::cout << (month < 10 ? "0" : "");
    std::cout << month << "." << year;
}
