#include "MemoryPool.h"

#include <cstdlib>
#include <iostream>
#include <functional>

#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>

const int threadNumMAX = 100;
const int threadCycles = 1000;
const int maxWaitTime = 10;
const size_t MIN_INTERVAL_SIZE = 2;
const size_t INTERVAL_SIZE_SPREAD = 50;

std::mutex outputMutex;

void userThread(int threadNum, MemoryPool& mp);

int main()
{
    srand(time(NULL));

    MemoryPool mp(BYTES_IN_8_MB);
    std::vector<std::thread> threads;
    int threadNum = 0;

    for (; threadNum < threadNumMAX; threadNum++) {
        threads.push_back(std::thread(userThread, threadNum, std::ref(mp)));
    }

    for (threadNum = 0; threadNum < threadNumMAX; threadNum++) {
        threads[threadNum].join();
    }

    return 0;
}

void userThread(int threadNum, MemoryPool& mp)
{
    size_t intervalLen = rand() % INTERVAL_SIZE_SPREAD + MIN_INTERVAL_SIZE;
    int* localPtr = (int*)mp.allocate(intervalLen * sizeof(int));
    auto end = localPtr + intervalLen;
    auto tmp = localPtr;

    for (; tmp!=end; tmp++) {
            *tmp = threadNum;
    }

    for (int i = 0; i < threadCycles; i++) {
        size_t tmpLength = intervalLen;
        intervalLen = rand() % INTERVAL_SIZE_SPREAD + MIN_INTERVAL_SIZE;
        localPtr = (int*)mp.reallocate(localPtr, intervalLen*sizeof(int));
        end = localPtr + intervalLen;
        tmp = localPtr + tmpLength;

        for (; tmp < end; tmp++) {
                *tmp = threadNum;
        }

        std::this_thread::sleep_for(
            std::chrono::microseconds(rand() % maxWaitTime + 1));
        std::lock_guard<std::mutex> guard(outputMutex);
        std::cout  << "Pointer at: " << localPtr <<
        " Thread number: " << threadNum << std::endl;

        end = localPtr + intervalLen - 1;
        tmp = localPtr;

        for (; tmp != end; tmp++) {
            std::cout << *tmp << "\t";
        }

        std::cout << *tmp << std::endl;
    }
    mp.freeMemory(localPtr);
}
