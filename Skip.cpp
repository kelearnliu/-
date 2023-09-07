#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int endPoint=nums[0];
        int index=0;
        while(index<= endPoint)
        {
            endPoint = max(endPoint,index+nums[index]);
            cout<<"index:"<<index<<"endPoint: "<<endPoint<<endl;
            if(endPoint>=nums.size())
                return true;
            ++index;
        }
        return false;
    }
};

int main()
{
    vector<int> nums{2,3,1,1,4};
    cout<<Solution().canJump(nums)<<endl;

}
