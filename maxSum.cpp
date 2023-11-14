////#include <iostream>
////#include <vector>
////#include <algorithm>
////using namespace std;
////int find_max_sum(vector<int>& a)
////{
////    int n = a.size();
////    int curSum = a[0];
////    int maxSum = a[0];
////
////    for(int i=1;i<n;i++)
////    {
////        cout<<"i = "<<i<<endl;
////        curSum = max(a[i],curSum+a[i]);
////        maxSum = max(curSum,maxSum);
////        cout<<"curSum = "<<curSum<<endl;
////        cout<<"maxSum = "<<maxSum<<endl;
////        cout<<"------"<<endl;
////    }
////    return maxSum;
////}
////int main()
////{
////    // {1,-2,3,5,-4,6}
////    // {1,1,3,8,8,10}
////    vector<int> a = {1,-2,3,5,-4,6};
//////    vector<int> a = {11,-2,1,-60,8,-2,3};
////    cout<<find_max_sum(a);
////    return 0;
////}
//
//#include <stdio.h>
//#include <stddef.h>
//#include <iostream>
//#include <cmath>
//using namespace std;
//char *f() {
//    char *X = "hello world";
//    return X + 6;
//}
//
//void t0()
//{
//    int l=3,r=10;
//    int count=0;
//    for(int i=l;i<=r;i++)
//    {
//        int res= log2(i);
//        if(2^res==i)
//        {
//            count= max(count,res);
//        }
//    }
//    cout<<count<<endl;
//}
//
//#include <iostream>
//
//int countEvenFactors(int num) {
//    int count = 0;
//    while (num % 2 == 0) {
//        count++;
//        num /= 2;
//    }
//    return count;
//}
//
//int findMaxPreference(int l, int r) {
//    int maxPreference = -1;
//    int result = -1;
//
//    for (int num = l; num <= r; num++) {
//        int preference = countEvenFactors(num);
//        if (preference > maxPreference) {
//            maxPreference = preference;
//            result = num;
//        }
//    }
//
//    return result;
//}
//
//
//
//void t1()
//{
//    int l, r;
//    std::cout << "Enter the left and right boundaries (l and r): ";
//    std::cin >> l >> r;
//
//    int favoriteNumber = findMaxPreference(l, r);
//    int favoritePreference = countEvenFactors(favoriteNumber);
//
//    std::cout << "Favorite number in the range [" << l << "," << r << "]: " << favoriteNumber << std::endl;
//    std::cout << "Favorite preference: " << favoritePreference << std::endl;
//}
//int main(int argc, char *argv[]) {
////    printf("%s", f());
//
//    t1();
//    return 0;
//}
#include <iostream>
#include <vector>

bool canMakeArrayEqual(std::vector<int>& a) {
    int sum = 0;
    int maxX = a[0];

    for (int num : a) {
        sum += num;
        maxX = std::max(maxX, num);
    }

    // 判断是否可以通过操作使所有元素相等
    return (sum % a.size() == 0) && ((maxX * a.size() - sum) % 2 == 0);
}

class A{
public:
    int a=0;
    const int b=99;
    void f1() const
    {
        std::cout<<"const function"<<std::endl;
        std::cout<<a<<std::endl;
        std::cout<<b<<std::endl;
    }
    void f2()
    {
        std::cout<<"normal function"<<std::endl;
        std::cout<<a+1<<std::endl;
        std::cout<<b+1<<std::endl;
    }

};
int main() {
   const A constA;
   A normalA;
   constA.f1();
   constA.f2();
   normalA.f1();
   normalA.f2();

    return 0;
}
