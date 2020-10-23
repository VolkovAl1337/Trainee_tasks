#include "MemoryPool.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <chrono>

const int threadNumMAX = 100;
const int threadCycles = 1000;
const int maxWaitTime = 10;
const size_t MAX_POOL_SIZE = 1.24e+9; //1 GB in bytes
const size_t MIN_INTERVAL_SIZE = 2;
const size_t INTERVAL_SIZE_SPREAD = 50;
MemoryPool mp;
std::mutex mt;

void userThread(int threadNum);

int main()
{
    srand(time(NULL));
    std::vector<std::thread> threads;
    int threadNum;

    for (threadNum = 0; threadNum < threadNumMAX; threadNum++) {
        threads.push_back(std::thread(userThread, threadNum));
    }

    for (threadNum = 0; threadNum < threadNumMAX; threadNum++) {
        threads[threadNum].join();
    }

    return 0;
}

void userThread(int threadNum)
{
    std::thread::id threadID = std::this_thread::get_id();
    int* localPtr = nullptr;
    size_t intervalLen = rand() % INTERVAL_SIZE_SPREAD + MIN_INTERVAL_SIZE;
    {
        std::lock_guard<std::mutex> guard(mt);
        localPtr = (int*)mp.allocate(intervalLen * sizeof(int));
    }

    for (int j = 0; j < intervalLen; j++) {
            *(localPtr + j) = threadNum;
    }

    for (int i = 0; i < threadCycles; i++) {
        size_t tmpLength = intervalLen;
        intervalLen = rand() % INTERVAL_SIZE_SPREAD + MIN_INTERVAL_SIZE;

        {
            std::lock_guard<std::mutex> guard(mt);
            localPtr = (int*)mp.reallocate(localPtr, intervalLen*sizeof(int));
        }

        for (; tmpLength<intervalLen; tmpLength++) {
            *(localPtr + tmpLength) = threadNum;
        }

        std::this_thread::sleep_for(
            std::chrono::microseconds(rand() % maxWaitTime + 1));
        std::lock_guard<std::mutex> guard(mt);
        std::cout  << "Pointer at: " << localPtr << " Thread ID: " <<
            threadID << " Thread number: " << threadNum << std::endl;
        int j = 0;

        for (; j < intervalLen - 1; j++) {
            std::cout << *(localPtr + j) << "\t";
        }

        std::cout << *(localPtr + j) << std::endl;
    }
    std::lock_guard<std::mutex> guard(mt);
    mp.freeMemory(localPtr);
}
