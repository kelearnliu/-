//
// Created by MI on 2023/8/24.
//
// 给定数组和一个N，要求数组像后轮转N次以后 输出
#include <vector>
#include "pv.h"
using namespace std;


void reverseV(vector<int>& nums, size_t start, size_t end)
{
    while(start < end)
    {
        swap(nums[start++],nums[end--]);
    }
}

int main()
{
    vector<int> nums{1,2,3,4,5,6,7};
    printVec(nums);
    size_t N=3;
    size_t n = nums.size();
    if(N%n==0)return 0;

    reverseV(nums,0,n-1);
    reverseV(nums,0,N-1);
    reverseV(nums,N,n-1);
    printVec(nums);
}