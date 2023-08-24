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
#include "pv.h"
using namespace std;

vector<vector<int>> threeSum() {
    vector<int> nums = { -1,0,1,2,-1,-4 };
    printVec(nums);
    vector<vector<int>> vv;
    // 默认是升序排列的
    int n = nums.size();
    sort(nums.begin(), nums.end());
    printVec(nums);
    // 这里要考虑的是当tmp所指向的数字是相同的时候 要作去重的工作 因为
    // 因为同样的tmp对应的结果其实是一样的
    for (int i = 0; i < n; i++) {
        if (nums[i] > 0)
            return vv;
        // 如果当前值和上一个相同，就不要了跳过  细节
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        int left_index = i + 1;
        int right_index = n - 1;
        while (left_index < right_index) {
            int count = nums[i] + nums[left_index] + nums[right_index];
            if (count > 0) right_index--;
            else if (count < 0) left_index++;
            else
            {
                vv.push_back(vector<int>{nums[i], nums[left_index], nums[right_index]});
                //cout << "push_back" << endl;
                //printVVec(vv);
                // 此时对left和right去重
                while (left_index < right_index  && nums[right_index] == nums[right_index - 1]) { right_index--; }
                while (left_index < right_index  && nums[left_index] == nums[left_index + 1]) { left_index++; }
                // 更新
                right_index--;
                left_index++;
            }
        }
    }
    cout << "结果是" << endl;
    return vv;
}

int main()
{
    printVVec(threeSum());
    return 0;
}