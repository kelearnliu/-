#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;




class Solution {
public:
    // 字母的开头和结束 是左闭右闭区间
    void rWord(string& s, int startIndex, int endIndex)
    {
        while(startIndex<endIndex)
        {
            swap(s[startIndex],s[endIndex]);
            startIndex++;endIndex--;
        }
    }
    string reverseWords(string s) {
        int startIndex = 0;
        int endIndex = s.length()-1;
        // 去掉开头的空格
        while(s[startIndex]==' ')
        {
            startIndex++;
        }
        while (s[endIndex]==' ')
        {
            endIndex--;
        }
        s = s.substr(startIndex,endIndex-startIndex+1);

        // 去掉中间的空格
        int fast=0,slow=0;
        int n = s.length();
        for(;fast<n;fast++)
        {
            if(s[fast] != ' ')
            {
                //case1 第一个
                if(slow != 0) s[slow++]=' ';
                while(fast<n && s[fast]!=' ')
                {
                    s[slow++] = s[fast++];
                }
            }
        }
        s.resize(slow);


        fast=0,slow=0;
        n = s.length();
        for(;fast < n;fast++) {
            if ((s[fast] != ' ' && s[fast + 1] == ' ') || fast==n-1)
            {
                rWord(s, slow, fast);
            }
            if (s[fast] == ' ' && s[fast + 1] != ' ')
            {
                slow=fast+1;
                fast=slow;
            }
        }
        reverse(s.begin(),s.end());

        return s;
    }
};
int main()
{
    string s{" hello w  world  "};
    cout<<"original:"<<endl;
    cout<<s<<endl;
    cout<<"reverse:"<<endl;
    cout<<Solution().reverseWords(s)<<endl;
}