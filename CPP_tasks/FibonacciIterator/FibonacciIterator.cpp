#include "FibonacciIterator.h"

FibIter::FibIter() = default;

FibIter::FibIter(int older, int cur, int iter) :
    oldNum(older), currentNum(cur), iteration(iter) {}

FibIter& FibIter::operator ++()
{
    int tmp = currentNum;
    currentNum += oldNum;
    oldNum = tmp;
    iteration += 1;

    return *this;
}

FibIter& FibIter::operator --()
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

bool FibIter::operator!= (const FibIter &it) const
{
    return iteration != it.iteration;
}

int FibIter::operator* () const
{
    return currentNum;
}

int FibIter::setIteration(int iter)
{
    if (iter < 0) {
        throw NegativeIterationException();
    }

    if (iteration > iter) {
        for (;iteration > iter;) {
            --(*this);
        }
        return currentNum;
    }

    for (;iteration < iter;) {
        ++(*this);
    }
    return currentNum;
}

int FibIter::getIteration()
{
    return iteration;
}
