#include "DateClass.h"
#include <iostream>

int main()
{
    Date d1(3, 3, 2000);

    d1.print();
    std::cout << std::endl;

    --d1;
    --d1;
    --d1;

    d1.print();
    std::cout << std::endl;

    Date d2 = d1;

    //d2.setYear(1900); - exception, 1900 isn't leap year

    d2.setMonth(5);
    d2.setDay(30);

    d2.print();
    std::cout << std::endl;

    ++d2;
    ++d2;
    ++d2;

    d2.print();
    std::cout << std::endl;
    return 0;
}
