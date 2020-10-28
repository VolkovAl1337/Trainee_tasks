#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

#include "MemoryPool.h"

const int THREAD_MAX_NUM = 100;
const int THREAD_CYCLES = 1000;
const int MAX_WAIT_TIME = 10;
const size_t MIN_INTERVAL_SIZE = 200;
const size_t INTERVAL_SIZE_SPREAD = 800;
const size_t ALLOC_POOL_SIZE = 10e+3;
std::mutex outputMutex;

void userThread(int threadNum, MemoryPool& mp);
void threadPrint(int threadNum, int* localPtr, size_t intervalLen);


int main()
{
    srand(time(NULL));

    MemoryPool mp(ALLOC_POOL_SIZE);
    std::vector<std::thread> threads;
    int threadNum = 0;

    for (; threadNum < THREAD_MAX_NUM; threadNum++) {
        threads.push_back(std::thread(userThread, threadNum, std::ref(mp)));
    }

    for (threadNum = 0; threadNum < THREAD_MAX_NUM; threadNum++) {
        threads[threadNum].join();
    }

    return 0;
}

void threadPrint(int threadNum, int* localPtr, size_t intervalLen)
{
    std::lock_guard<std::mutex> guard(outputMutex);
    std::cout  << "Pointer at: " << localPtr <<
        " Thread number: " << threadNum << "\t Size: " <<
        intervalLen << std::endl;

    auto end = localPtr + intervalLen - 1;
    auto tmp = localPtr;

    for (; tmp != end; tmp++) {
        std::cout << *tmp << "\t";
    }

    std::cout << *tmp << std::endl;
}

void userThread(int threadNum, MemoryPool& mp)
{
    size_t intervalLen = rand() % INTERVAL_SIZE_SPREAD + MIN_INTERVAL_SIZE;
    int* localPtr = nullptr;

    try
    {
        localPtr = (int*)mp.allocate(intervalLen * sizeof(int));
    }
    catch(...)
    {
        std::lock_guard<std::mutex> guard(outputMutex);
        std::cerr << "An error occured during allocating memory for thread " <<
            threadNum << std::endl;
        return;
    }

    auto end = localPtr + intervalLen;
    auto tmp = localPtr;

    for (; tmp!=end; tmp++) {
        *tmp = threadNum;
    }

    for (int i = 0; i < THREAD_CYCLES; i++) {
        size_t tmpLength = intervalLen;
        intervalLen = rand() % INTERVAL_SIZE_SPREAD + MIN_INTERVAL_SIZE;

        try
        {
            localPtr = (int*)mp.reallocate(localPtr, intervalLen*sizeof(int));
        }
        catch(...)
        {
            std::lock_guard<std::mutex> guard(outputMutex);
            std::cerr << "An error occured during reallocating memory "
                "for thread " << threadNum << std::endl;
            intervalLen = tmpLength;
        }

        end = localPtr + intervalLen;
        tmp = localPtr + tmpLength;

        for (; tmp < end; tmp++) {
            *tmp = threadNum;
        }

        std::this_thread::sleep_for(
            std::chrono::microseconds(rand() % MAX_WAIT_TIME + 1));

        threadPrint(threadNum, localPtr, intervalLen);
    }
    mp.freeMemory(localPtr);
}
