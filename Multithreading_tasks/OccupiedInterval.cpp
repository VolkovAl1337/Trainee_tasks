#include "OccupiedInterval.h"

OccupiedInterval::OccupiedInterval(char* PtrToInterval, size_t sizeOfInterval) :
    occupPtr(PtrToInterval), occupPtrEnd(PtrToInterval + sizeOfInterval){};

void* OccupiedInterval::getPtr() const
{
    return occupPtr;
}

void* OccupiedInterval::getPtrEnd() const
{
    return occupPtrEnd;
}

size_t OccupiedInterval::getSize() const
{
    return occupPtrEnd - occupPtr;
}

bool OccupiedInterval::operator <(const OccupiedInterval& occInter) const
{
    return occupPtr < occInter.occupPtr;
}

bool OccupiedInterval::operator ==(const void* occPtr_) const
{
    return occupPtr == occPtr_;
}

bool OccupiedInterval::operator ==(const OccupiedInterval& occInter_) const
{
    return occInter_.occupPtr == occupPtr;
}

//returns pointer to start of an interval
char* OccupiedInterval::operator*() const
{
    return occupPtr;
}
