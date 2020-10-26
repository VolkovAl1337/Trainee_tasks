#ifndef FIBONACCIITERATOR_H
#define FIBONACCIITERATOR_H
class NegativeIterationException{};

class FibonacciIterator {
private:
    int iteration = 0;
    int oldNum = 0;
    int currentNum = 1;
public:
    FibonacciIterator();
    FibonacciIterator(int older, int cur, int iter);
    int operator*() const;
    int setIteration(const int& iter);
    int getIteration() const;
    FibonacciIterator& operator ++();
    FibonacciIterator& operator --();
    bool operator !=(const FibonacciIterator &it) const;
};
#endif
