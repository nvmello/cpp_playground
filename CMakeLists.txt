cmake_minimum_required(VERSION 3.30)
project(TradingSim)

set(CMAKE_CXX_STANDARD 20)

add_executable(TradingSim main.cpp
        LockFreeRingBuf/LockFreeRingBuffer.h
        LockFreeRingBuf/LockFreeRingBuffer.cpp)
