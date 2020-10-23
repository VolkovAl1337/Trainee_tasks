cmake_minimum_required(VERSION 2.8)

project(MultithreadingMemoryManagement)

set(SOURCE_EXE TestTarget.cpp)

set(SOURCE_LIB MemoryPool.cpp   OccupiedInterval.cpp)

add_library(MemoryPool STATIC ${SOURCE_LIB})
add_library(OccupiedInterval STATIC ${SOURCE_LIB})

add_executable(test ${SOURCE_EXE})
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS -pthread)
find_package(Threads REQUIRED)

target_link_libraries(test MemoryPool OccupiedInterval)