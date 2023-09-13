#include <vector>
#include <algorithm>
#include <iostream>
#include "pv.h"
using namespace std;
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int curSum = 0;
        int totalSum = 0;
        int start = 0;
        for (int i = 0; i < gas.size(); i++) {
            curSum += gas[i] - cost[i];
            totalSum += gas[i] - cost[i];
            // 之所以可以一次遍历得到结果  是因为只要totalsum>=0就一定能保证转一圈
            if (curSum < 0) {   // 当前累加rest[i]和 curSum一旦小于0
                cout<<"更新start: "<<start<<" to "<<i+1<<endl;
                start = i + 1;  // 起始位置更新为i+1
                curSum = 0;     // curSum从0开始

            }
        }
        if (totalSum < 0) return -1; // 说明怎么走都不可能跑一圈了
        return start;
    }
};
int main()
{
    vector<int>gas = {1,2,3,4,5}, cost = {3,4,5,1,2};
    cout<<Solution().canCompleteCircuit(gas,cost);
}