#include "MemoryPool.h"

inline void tooBigAllocCheck(size_t neededSize, size_t availableSize)
{
    if (neededSize > availableSize) {
        throw OutOfMemoryException();
    }
}

inline void tooSmallAllocCheck(size_t neededSize)
{
    if (neededSize < 1) {
        throw NegativeOrZeroException();
    }
}

MemoryPool::MemoryPool(const size_t& poolSize_)
{
    poolPtr = new char[poolSize_];
    poolSize = poolSize_;
}

void MemoryPool::reservePool(const size_t& poolSize_)
{
    if (poolPtr) {
        delete[] poolPtr;
    }

    poolPtr = new char[poolSize_];
    poolSize = poolSize_;
}

void* MemoryPool::allocate(const size_t& reserveSize)
{
    std::lock_guard<std::recursive_mutex> guard(mtMemory);
    size_t poolSizeTmp = poolSize;

    if (occupiedSpace.empty()) {
        tooBigAllocCheck(reserveSize, poolSize);
        occupiedSpace.push_back(OccupiedInterval(poolPtr, reserveSize));
        return poolPtr;
    }

    auto curInterv = occupiedSpace.begin();

    if(**curInterv != poolPtr && poolPtr + reserveSize <= **curInterv) {
        occupiedSpace.push_front(OccupiedInterval(poolPtr, reserveSize));
        return poolPtr;
    }

    auto nextInterv = std::next(curInterv);

    while (nextInterv != occupiedSpace.end()) {
        if (curInterv->occupPtrEnd + reserveSize <=
                **nextInterv) {
                occupiedSpace.insert(nextInterv,
                OccupiedInterval(curInterv->occupPtrEnd,
                reserveSize));
                return (curInterv->occupPtrEnd);
        }
        ++curInterv;
        ++nextInterv;
    }

    auto lastInterv = occupiedSpace.end();
    --lastInterv;
    size_t availableSpace = (poolPtr + poolSize) - lastInterv->occupPtrEnd;
    tooBigAllocCheck(reserveSize,  availableSpace);
    occupiedSpace.push_back(OccupiedInterval(
        lastInterv->occupPtrEnd, reserveSize));
    return lastInterv->occupPtrEnd;
}

void MemoryPool::freeMemory(const void* intervalPtr)
{
    std::lock_guard<std::recursive_mutex> guard(mtMemory);
    auto deleteElement = std::find(occupiedSpace.begin(),
        occupiedSpace.end(), intervalPtr);

    if (deleteElement != occupiedSpace.end()) {
        occupiedSpace.remove(*deleteElement);
    }
}

size_t MemoryPool::getPoolSize()
{
    return poolSize;
}

size_t MemoryPool::getIntervalSize(const void* intervaPtr)
{
    auto interval = std::find(occupiedSpace.begin(),
        occupiedSpace.end(), intervaPtr);

    if (interval == occupiedSpace.end()) {
        throw WrongPointerException();
    }

    return interval->getSize();
}

void* MemoryPool::reallocatePool(const size_t& poolSizeNew)
{
    std::lock_guard<std::recursive_mutex> guard(mtMemory);
    char* newPoolPtr = new char[poolSizeNew];
    delete[] poolPtr;
    poolPtr = newPoolPtr;
    poolSize = poolSizeNew;
    return poolPtr;
}

void* MemoryPool::reallocate(void* intervalPtr, const size_t& newIntervalSize)
{
    std::lock_guard<std::recursive_mutex> guard(mtMemory);
    tooBigAllocCheck(newIntervalSize, poolSize);
    tooSmallAllocCheck(newIntervalSize);

    auto interval = std::find(occupiedSpace.begin(),
        occupiedSpace.end(), intervalPtr);

    if (interval != occupiedSpace.end()) {
        size_t oldIntervalSize = interval->getSize();
        char* tmpIntervalEndPtr = **interval + newIntervalSize;

        if (oldIntervalSize >= newIntervalSize ||
        tmpIntervalEndPtr <= **(std::next(interval)) ||
        std::next(interval) == occupiedSpace.end()) {
            interval->occupPtrEnd = tmpIntervalEndPtr;
            return intervalPtr;
        } else {
            size_t availableSpace = (poolPtr + poolSize) - interval->occupPtrEnd;
            tooBigAllocCheck(newIntervalSize, availableSpace);
            char* tmpIntervalPtr = (char*)allocate(newIntervalSize);
            memcpy(tmpIntervalPtr, intervalPtr, oldIntervalSize);
            freeMemory(intervalPtr);
            interval->occupPtrEnd = (char*)intervalPtr + newIntervalSize;
            return tmpIntervalPtr;
        }
    } else {
        throw WrongPointerException();
    }
}

MemoryPool::~MemoryPool()
{
    delete[] poolPtr;
}
