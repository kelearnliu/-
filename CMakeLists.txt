cmake_minimum_required(VERSION 3.24)
project(Algorithm)

set(CMAKE_CXX_STANDARD 11)

add_executable(MultiThreadAtomic MultiThreadAtomic.cpp)
add_executable(MultiThreadASem MultiThreadASem.cpp)
add_executable(MultiThreadConditionVariable MultiThreadConditionVariable.cpp)
add_executable(MultiThreadMutex MultiThreadMutex.cpp)