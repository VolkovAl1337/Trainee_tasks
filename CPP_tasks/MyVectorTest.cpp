#include <iostream>
#include "MyVector.h"

int main() {
    Vector<int> a(5, 999);
    std::cout << "Vector size " << a.getSize() << std::endl;
    a.outputAll();
    std::cout << std::endl;
    std::cout << "=======================" << std::endl;
    a[0] = 10;
    a[1] = 11;
    a[2] = 22;
    a[3] = 33;
    a[4] = 44;


    a.outputAll();
    std::cout << std::endl;
    std::cout << "=======================" << std::endl;
    a[7] = 50;
    a[-2] = 9876;
    std::cout<<*a.front()<<" "<<*a.back()<<std::endl;

    a.pushBack(1212);

    a.outputAll();
    std::cout << std::endl;
    std::cout << "=======================" << std::endl;

    a.pushFront(865);

    a.outputAll();
    std::cout << std::endl;
    std::cout << "=======================" << std::endl;

    a.insert(777, 3);

    a.outputAll();
    std::cout << std::endl;
    std::cout << "=======================" << std::endl;

    a.insert(123, 10);

    a.outputAll();
    std::cout << std::endl;
    std::cout << "=======================" << std::endl;

    a.insert(654, -5);

    a.outputAll();
    std::cout << std::endl;
    std::cout << "=======================" << std::endl;

    a.insert(356, 0);

    a.outputAll();
    std::cout << std::endl;
    std::cout << "=======================" << std::endl;
    auto x = a.pop(3);
    auto x1 = a.popBack();
    auto x2 = a.popFront();
    std::cout<< x << " " << x1 << " " << x2 << std::endl;
    a.outputAll();
    std::cout << std::endl;
    return 0;
}
