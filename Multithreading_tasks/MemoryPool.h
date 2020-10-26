#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

#include "OccupiedInterval.h"

class OutOfMemoryException{};
class NegativeOrZeroException{};
class WrongPointerException{};

class MemoryPool
{
private:
    char* poolPtr;
    size_t poolSize;
    std::list<OccupiedInterval> occupiedSpace;
    std::recursive_mutex mtMemory;
public:
    MemoryPool(const size_t& poolSize_);
    void reservePool(const size_t& poolSize);
    void* allocate(const size_t& sizeOfOccupation);
    size_t getPoolSize();
    size_t getIntervalSize(const void* ptrToInterval);
    void freeMemory(const void* intervalPtr);
    void* reallocatePool(const size_t& poolSizeNew);
    void* reallocate(void* occupiedIntervalPtr, const size_t& newIntervalSize);
    ~MemoryPool();
};
#endif
