#include <iostream>
#include <vector>
#include <stack>
#include "pv.h"
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n=height.size();
        vector<int> left(n),right(n);
        int Lmax=0;
        for(int i=0;i<n;i++)
        {
            if(height[i]<Lmax)
            {
                left[i]=Lmax;
            }
            else
            {
                left[i]=height[i];
                Lmax=height[i];
            }
        }

        int Rmax=0;
        for(int i=n-1;i>=0;i--)
        {
            if(height[i]<Rmax)
            {
                right[i]=Rmax;
            }
            else
            {
                right[i]=height[i];
                Rmax=height[i];
            }
        }

        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=(min(right[i],left[i])-height[i]);
        }
        return sum;
    }

    int trap1(vector<int>& height)
    {
        int n=height.size();
        if(n<=2) return 0;
        stack<int> stk;
        stk.push(0);
        int sum=0;
        for(int i=1;i<n;i++)
        {
            // 单调栈中的元素一定要降序排列 并且计算是不断进行的 因为可能有v字型的情况
            // 计算完底部的 计算上面的
            while(!stk.empty() && height[i]>height[stk.top()])
            {
                int mid = stk.top();
                stk.pop();
                if(!stk.empty())
                {
                    int h = min(height[stk.top()],height[i])-height[mid];
                    int w = i - stk.top() -1;
                    sum += h*w;
                }
            }
            stk.push(i);
        }
        return sum;
    }
};

int main()
{
    vector<int> height{0,1,0,2,1,0,1,3,2,1,2,1};
    cout<<Solution().trap(height)<<endl;
    cout<<Solution().trap1(height);
}
