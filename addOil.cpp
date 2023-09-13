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
            // ֮���Կ���һ�α����õ����  ����ΪֻҪtotalsum>=0��һ���ܱ�֤תһȦ
            if (curSum < 0) {   // ��ǰ�ۼ�rest[i]�� curSumһ��С��0
                cout<<"����start: "<<start<<" to "<<i+1<<endl;
                start = i + 1;  // ��ʼλ�ø���Ϊi+1
                curSum = 0;     // curSum��0��ʼ

            }
        }
        if (totalSum < 0) return -1; // ˵����ô�߶���������һȦ��
        return start;
    }
};
int main()
{
    vector<int>gas = {1,2,3,4,5}, cost = {3,4,5,1,2};
    cout<<Solution().canCompleteCircuit(gas,cost);
}