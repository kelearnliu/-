//
// Created by MI on 2023/8/28.
//
#include <iostream>
#include <future>
using namespace std;

void func(std::promise<int>& f)
{
    f.set_value(10);
}
int main()
{
    std::promise<int> f;
    auto future_result = f.get_future();

    std::thread t1(func,std::ref(f));
    t1.join();

    cout<<future_result.get()<<endl;
    return 0;
}