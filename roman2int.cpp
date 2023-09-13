#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include "pv.h"
using namespace std;


class Solution {
public:
    vector<int> res;
    void trans(string s)
    {
        if(s.length()==0)
            return ;
        map<char,int> myMap;
        myMap.insert(make_pair('I',1));
        myMap.insert(make_pair('V',5));
        myMap.insert(make_pair('X',10));
        myMap.insert(make_pair('L',50));
        myMap.insert(make_pair('C',100));
        myMap.insert(make_pair('D',500));
        myMap.insert(make_pair('M',1000));
        res.push_back(myMap[s[0]]);
//        cout<<res.back()<<endl;
        s = s.substr(1);
        romanToInt(s);
    }
    int romanToInt(string s) {
        trans(std::move(s));
        int startIndex=0;
        int ret=0;
        while (startIndex<res.size())
        {
            if(res[startIndex]>=res[startIndex+1] || startIndex==res.size()-1)
            {
                ret += res[startIndex];
            }
            else{
                ret -= res[startIndex];
            }
            startIndex++;
        }
        return ret;
    }
};


int main()
{
    Solution s1;
//    string s= "LVIII";
//    string s= "IX";
//    string s= "IV";
    string s= "III";
    int ret = s1.romanToInt(s);
    cout<<ret<<endl;
    printVec(s1.res);
    return 0;
}