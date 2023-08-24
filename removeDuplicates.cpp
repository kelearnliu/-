//
// Created by MI on 2023/8/24.
//
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
#include <stack>
#include <iterator>
#include <complex>
#include <algorithm>
#include <queue>
using namespace std;



int removeDuplicates() {
    vector<int> nums{ 0,0,1,1,1,1,2,3,3 };
    if (nums.size() <= 2)
    {
        return nums.size();
    }

    int slow = 2, fast = 2;
    while (fast < nums.size())
    {
        if (nums[fast] != nums[fast - 2])
        {
            nums[slow++] = nums[fast];
        }
        else
            fast++;
    }
    return slow;

}

int main()
{
    removeDuplicates();
    return 0;
}