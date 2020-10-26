#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H
#include "OccupiedInterval.h"

#include <iostream>
#include <cstring>

#include <list>
#include <algorithm>
#include <mutex>
#include <thread>

const size_t BYTES_IN_8_MB = 8e+6;
const size_t MAX_SPACE = 1.24e+9; //1 GB

class OutOfMemoryException{};
class TooSmallException{};
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
