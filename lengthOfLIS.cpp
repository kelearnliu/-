//
// Created by wxy on 2023/10/12.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include "pv.h"

using namespace std;

void t1(vector<int>& a)
{
    printVec(a);
    vector<int> b;
    int n=a.size();
    vector<int> dp(n,1);
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(a[i]>a[j])
            {
                dp[i]= max(dp[i],dp[j]+1);
            }
        }
    }
    printVec(dp);
    cout<<*max_element(dp.begin(),dp.end());
}

void t2(vector<int>& a)
{

}
int main()
{
    vector<int> a{10,9,2,5,3,7,101,18};
    t1(a);
    t2(a);
    return 0;
}