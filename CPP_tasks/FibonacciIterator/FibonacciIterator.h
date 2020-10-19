#ifndef FIBONACCIITERATOR_H
#define FIBONACCIITERATOR_H
class NegativeIterationException{};

class FibIter {
private:
    int iteration = 0;
    int oldNum = 0;
    int currentNum = 1;
public:
    FibIter();
    FibIter(int older, int cur, int iter);
    int operator*() const;
    int setIteration(int iter);
    int getIteration();
    FibIter& operator ++();
    FibIter& operator --();
    bool operator !=(const FibIter &it) const;
};
#endif
