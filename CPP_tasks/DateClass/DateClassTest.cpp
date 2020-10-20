#include "Date.h"
#include <iostream>

int main()
{
    Date d1(3, 3, 2000);

    std::cout << d1 << std::endl;

    Date d2 = d1;

    d2.setDay(29);
    d2.setMonth(2);

    std::cout << d2 << std::endl;

    d2.addDays(10);
    std::cout << d2 << std::endl;
    d2.addDays(-10);
    std::cout << d2 << std::endl;
    d2.addMonths(-1);
    std::cout << d2 << std::endl;
    d2.addMonths(1);
    std::cout << d2 << std::endl;
    return 0;
}
