#include "FibonacciIterator.h"
#include <iostream>

int main()
{
    FibIter fibSeq;
    FibIter fibSeq1(1, 1, 10);
    std::cout << *fibSeq << " iteration: "<< fibSeq.getIteration() << std::endl;
    fibSeq.setIteration(5);
    std::cout << *fibSeq << " iteration: "<< fibSeq.getIteration() << std::endl;
    fibSeq.setIteration(3);
    std::cout << *fibSeq << " iteration: "<< fibSeq.getIteration() << std::endl;
    fibSeq.setIteration(6);
    std::cout << *fibSeq << " iteration: "<< fibSeq.getIteration() << std::endl;
    ++fibSeq;
    std::cout << *fibSeq << " iteration: "<< fibSeq.getIteration() << std::endl;
    --fibSeq;
    std::cout << *fibSeq << " iteration: "<< fibSeq.getIteration() << std::endl;

    while (fibSeq != fibSeq1)
    {
        ++fibSeq;
        std::cout << *fibSeq << " iteration: "<< fibSeq.getIteration() << std::endl;
    }

    return 0;
}