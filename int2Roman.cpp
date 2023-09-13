#include <vector>
#include <string>
#include <map>
#include "pv.h"
using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        int tmp=num;
        vector<int> res;
        vector<int> n{1,5,10,50,100,500,1000};
        for(int i=n.size()-1;i>=0;i--)
        {
            int k=num/n[i];
            num %= n[i];
            res.push_back(k);
        }
//        cout<<"res:"<<endl;
        printVec(res);


        vector<int> ans(4);
        ans[0]=res[0]*1000;
        ans[1]=res[1]*500+res[2]*100;
        ans[2]=res[3]*50+res[4]*10;
        ans[3]=res[5]*5+res[6]*1;
        cout<<"ans:"<<endl;
        printVec(ans);
        string ret="";
        vector<string> thousand{"","M","MM","MMM"};
        vector<string> hundred{"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
        vector<string> ten{"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
        vector<string> digit{"","I","II","III","IV","V","VI","VII","VIII","IX"};

        string a1=thousand[ans[0]/1000];
        string a2=hundred[ans[1]/100];
        string a3=ten[ans[2]/10];
        string a4=digit[ans[3]/1];

        cout<<a1<<endl;
        cout<<a2<<endl;
        cout<<a3<<endl;
        cout<<a4<<endl;

        ret+=a1+=a2+=a3+=a4;
        return ret;
    }
};
int main()
{
    int num=1994;
    string res = Solution().intToRoman(num);
    cout<<res<<endl;
    return 0;
}