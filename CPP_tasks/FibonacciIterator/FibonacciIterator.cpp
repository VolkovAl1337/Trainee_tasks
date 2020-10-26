#include "FibonacciIterator.h"

FibonacciIterator::FibonacciIterator() = default;

FibonacciIterator::FibonacciIterator(int older, int cur, int iter) :
    oldNum(older), currentNum(cur), iteration(iter) {}

FibonacciIterator& FibonacciIterator::operator ++()
{
    int tmp = currentNum;
    currentNum += oldNum;
    oldNum = tmp;
    iteration += 1;

    return *this;
}

FibonacciIterator& FibonacciIterator::operator --()
{
    if (iteration == 0) {
        throw NegativeIterationException();
    }

    int tmp = oldNum;
    oldNum = currentNum - oldNum;
    currentNum = tmp;
    iteration -= 1;

    return *this;
}

bool FibonacciIterator::operator!= (const FibonacciIterator &it) const
{
    return iteration != it.iteration;
}

int FibonacciIterator::operator* () const
{
    return currentNum;
}

int FibonacciIterator::setIteration(const int& iter)
{
    if (iter < 0) {
        throw NegativeIterationException();
    }

    for (;iteration > iter;) {
        --(*this);
    }

    for (;iteration < iter;) {
        ++(*this);
    }
    return currentNum;
}

int FibonacciIterator::getIteration() const
{
    return iteration;
}
