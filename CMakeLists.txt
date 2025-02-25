cmake_minimum_required(VERSION 3.30)
project(Cpp_Playground)

set(CMAKE_CXX_STANDARD 20)

add_executable(Cpp_Playground main.cpp
        LockFreeRingBuf/LockFreeRingBuffer.h
        LockFreeRingBuf/LockFreeRingBuffer.cpp
        Cache/LRU/LRU_Cache.h
        Cache/LRU/LRU_Cache.cpp
)
