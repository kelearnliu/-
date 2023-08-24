cmake_minimum_required(VERSION 3.24)
project(Algorithm)

set(CMAKE_CXX_STANDARD 20)

# 当前文件夹下面的所有.h文件包含进去
include_directories(${CMAKE_SOURCE_DIR})
#include_directories("pv.h")


add_executable(multiThreadAtomic multiThreadAtomic.cpp)
add_executable(multiThreadASem multiThreadASem.cpp)
add_executable(multiThreadConditionVariable multiThreadConditionVariable.cpp)
add_executable(multiThreadMutex multiThreadMutex.cpp)

add_executable(threeSum threeSum.cpp)
add_executable(fourSum fourSum.cpp)
add_executable(islandDFS islandDFS.cpp)
add_executable(mergeTwoLists mergeTwoLists.cpp)
add_executable(removeDuplicates removeDuplicates.cpp)
add_executable(removeNthFromEnd removeNthFromEnd.cpp)
add_executable(reverseList reverseList.cpp)
add_executable(reverseWords reverseWords.cpp)
add_executable(rotateNList rotateNList.cpp)
add_executable(rotateNVector rotateNVector.cpp)