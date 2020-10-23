#ifndef OCCUPIEDINTERVAL_H
#define OCCUPIEDINTERVAL_H
#include <iostream>


struct OccupiedInterval
{
    friend class MemoryPool;
private:
    char* occupPtr;
    char* occupPtrEnd;
public:
    OccupiedInterval (char* ptrToInterval, size_t sizeOfInterval);
    void* getPtr() const;
    void* getPtrEnd() const;
    size_t getSize() const;
    bool operator <(const OccupiedInterval& occInter) const;
    bool operator ==(const void* occPtr_) const;
    bool operator ==(const OccupiedInterval& OccupInter_) const;
    char* operator*() const;
};
#endif
