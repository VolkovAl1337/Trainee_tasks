#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H
#include "OccupiedInterval.h"
#include <list>
#include <iostream>
#include <algorithm>
#include <cstring>

const size_t bytesIn8MB = 8e+6;
const size_t maxSpace = 1.24e+9;

class TooBigPoolException{};
class WrongPointerException{};

class MemoryPool
{
private:
    char* poolPtr;
    size_t poolSize;
    std::list<OccupiedInterval> occupiedSpace;
public:
    MemoryPool();
    MemoryPool(const size_t& poolSize_);
    void reservePool(const size_t& poolSize);
    void* allocate(const size_t& sizeOfOccupation);
    size_t getMemory() const;
    size_t getIntervalSize(const void* ptrToInterval) const;
    void freeMemory(const void* intervalPtr);
    void* reallocatePool(const size_t& poolSizeNew);
    void* reallocate(void* occupiedIntervalPtr, const size_t& newIntervalSize);
    ~MemoryPool();
};
#endif
