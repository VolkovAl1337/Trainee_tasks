#include "MemoryPool.h"

inline void tooBigCheck(size_t neededSize, size_t availableSize) {
    if (neededSize > availableSize) {
        throw TooBigPoolException();
    }
}

//allocate 8 mb
MemoryPool::MemoryPool()
{
    poolPtr = new char[bytesIn8MB];
    poolSize = bytesIn8MB;
}

MemoryPool::MemoryPool(const size_t& poolSize_)
{
    tooBigCheck(poolSize_, maxSpace);
    poolPtr = new char[poolSize_];
    poolSize = poolSize_;
}

void MemoryPool::reservePool(const size_t& poolSize_) {
    tooBigCheck(poolSize_, maxSpace);

    if (poolPtr){
      delete[] poolPtr;
    }

    poolPtr = new char[poolSize_];
    poolSize = poolSize_;
}

void* MemoryPool::allocate(const size_t& reserveSize)
{
    size_t poolSizeTmp = poolSize;

    if (occupiedSpace.empty()) {
        tooBigCheck(reserveSize, maxSpace);
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
    tooBigCheck(reserveSize,  availableSpace);
    occupiedSpace.push_back(OccupiedInterval(
        lastInterv->occupPtrEnd, reserveSize));

    return lastInterv->occupPtrEnd;
}

void MemoryPool::freeMemory(const void* intervalPtr)
{
    auto deleteElement = std::find(occupiedSpace.begin(),
        occupiedSpace.end(), intervalPtr);

    if (deleteElement != occupiedSpace.end()) {
        occupiedSpace.remove(*deleteElement);
    }
}

size_t MemoryPool::getMemory() const
{
    return poolSize;
}

size_t MemoryPool::getIntervalSize(const void* intervaPtr) const
{
    auto interval = std::find(occupiedSpace.begin(),
        occupiedSpace.end(), intervaPtr);

    if (interval != occupiedSpace.end()) {
        return interval->getSize();
    } else {
        throw WrongPointerException();
    }
}

void* MemoryPool::reallocatePool(const size_t& poolSizeNew)
{
    tooBigCheck(poolSizeNew, poolSize);
    char* newPoolPtr = new char[poolSizeNew];
    delete[] poolPtr;
    poolPtr = newPoolPtr;
    poolSize = poolSizeNew;
    return poolPtr;
}

void* MemoryPool::reallocate(void* intervalPtr, const size_t& newIntervalSize)
{
    tooBigCheck(newIntervalSize, poolSize);

    auto interval = std::find(occupiedSpace.begin(),
        occupiedSpace.end(), intervalPtr);

    if (interval != occupiedSpace.end()) {
        size_t oldIntervalSize = interval->getSize();
        char* tmpIntervalEndPtr = **interval + newIntervalSize;

        if (oldIntervalSize >= newIntervalSize ||
        tmpIntervalEndPtr <= **(std::next(interval)) ||
        std::next(interval) == occupiedSpace.end()) {
            //std::cout << "Looks like it fits..." << std::endl;
            interval->occupPtrEnd = tmpIntervalEndPtr;

            return intervalPtr;
        } else {
            size_t availableSpace = (poolPtr + poolSize) - interval->occupPtrEnd;
            tooBigCheck(newIntervalSize, availableSpace);
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
    std::cout << "deleted pointer" << std::endl;
}
