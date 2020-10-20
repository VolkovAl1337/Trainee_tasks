#include "FibonacciIterator.h"

FibonacciIterarot::FibonacciIterarot() = default;

FibonacciIterarot::FibonacciIterarot(int older, int cur, int iter) :
    oldNum(older), currentNum(cur), iteration(iter) {}

FibonacciIterarot& FibonacciIterarot::operator ++()
{
    int tmp = currentNum;
    currentNum += oldNum;
    oldNum = tmp;
    iteration += 1;

    return *this;
}

FibonacciIterarot& FibonacciIterarot::operator --()
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

bool FibonacciIterarot::operator!= (const FibonacciIterarot &it) const
{
    return iteration != it.iteration;
}

int FibonacciIterarot::operator* () const
{
    return currentNum;
}

int FibonacciIterarot::setIteration(const int& iter)
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

int FibonacciIterarot::getIteration() const
{
    return iteration;
}
