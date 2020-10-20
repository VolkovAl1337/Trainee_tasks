#ifndef DATECLASS_H
#define DATECLASS_H

class TooBigMonthException{};
class TooBigDayException{};
class TooSmallMonthException{};
class TooSmallDayException{};

class Date {
private:
    int day = 5;
    int month = 5;
    int year = 1999;
public:
    Date();
    Date(int day, int month, int year);
    Date(const Date& d1);
    void dayMonthCheck(int day, int month, int year);
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    int getDay();
    int getMonth();
    int getYear();
    Date& operator ++();
    Date& operator --();
    void print();
};
#endif
