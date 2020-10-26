#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <map>

const int maxMonthNum = 12;
const int shortFebLength = 28;
const int longFebLength = 29;
const int febNum = 2;
const int decBase = 10;

class WrongDateException{};

struct Date {
private:
    int day;
    int month;
    int year;
    static std::map<int, int> monthLenths;

public:
    Date();
    Date(int day, int month, int year);
    Date(const Date& d1);
    inline bool isLeapYear(int year) const;
    bool isDateCorrect(int day, int month, int year) const;
    void setDay(const int& day);
    void setMonth(const int& month);
    void setYear(const int& year);
    int getDay() const;
    int getMonth() const;
    int getMonthLength() const;
    int getYear() const;
    void addDays(int days);
    void addMonths(int months);
    void addYears(int years);
    void subDays(int days);
    void subMonths(int months);
    void subYears(int yeats);
};

std::ostream& operator <<(std::ostream& os, const Date& dt);

#endif
