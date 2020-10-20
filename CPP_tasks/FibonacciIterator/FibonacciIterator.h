#ifndef FIBONACCIITERATOR_H
#define FIBONACCIITERATOR_H
class NegativeIterationException{};

class FibonacciIterarot {
private:
    int iteration = 0;
    int oldNum = 0;
    int currentNum = 1;
public:
    FibonacciIterarot();
    FibonacciIterarot(int older, int cur, int iter);
    int operator*() const;
    int setIteration(const int& iter);
    int getIteration() const;
    FibonacciIterarot& operator ++();
    FibonacciIterarot& operator --();
    bool operator !=(const FibonacciIterarot &it) const;
};
#endif
