#include <vector>
#include <string>
#include <algorithm>
#include "pv.h"

using namespace std;
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ret="";
        sort(strs.begin(),strs.end(),
             [](const string& a,const string& b){return a.size()<b.size();});
        printVec(strs);
        int lmin = strs[0].size();
        cout<<"lmin: "<<lmin<<endl;
        // index�ǿ���ÿ���ַ�����Ԫ�ص�����
        int index=0;
        int cnt=0;
        int n=strs.size();
        // i�ǿ���strs�еĲ�ͬ�ַ��������
        int i=0;
        while(index<lmin && i<n)
        {
            // ��i���ַ� ��indexλ �������ÿ���ַ���indexλ
            char tmp=strs[i][index];
            cout<<tmp<<endl;
            bool flag=1;
            for(auto& str:strs)
            {
                flag = (tmp==str[index])?1:0;
                tmp=str[index];
                cout<<"str: "<<str<<"\tindex: "<<index<<"\tflag: "<<flag<<endl;
            }

            if(flag) {
                cnt++;
            }
            else
            {
                break;
            }
            index++;i++;
        }

        if(cnt==0){
            return "";
        }
        else
        {
            return strs[0].substr(0,cnt);
        }

    }
};

int main()
{
//    vector<string> strs{"flower","flow","flight"};
    vector<string> strs{"dog","racecar","car"};

    cout<<Solution().longestCommonPrefix(strs)<<endl;
    cout<<"output"<<endl;
    return 0;
}