#include <vector>
#include <string>
#include <algorithm>

#include "pv.h"

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        reverse(s.begin(),s.end());
        int startIndex=0;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]==' ')
            {
                startIndex++;
            }
            else
                break;
        }
        s = s.substr(startIndex);
        int len=0;
        for(int i=0;i<s.length()-startIndex+1;i++)
        {
            if(s[i]==' ')
            {
                len = i;
                break;
            }
        }
        return len;
    }
};

int main()
{
    cout<<Solution().lengthOfLastWord("hello world  ");
    return 0;
}