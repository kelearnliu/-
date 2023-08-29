//
// Created by MI on 2023/8/28.
//
#include <iostream>
#include <future>
using namespace std;

int func()
{
    int i=0;
    for(;i<10;i++)
    {
        i++;
    }
    return i;
}



int main()
{
    //1 直接启动线程
    std::future<int> future_res=std::async(std::launch::async, func);

    // 2 封装成packet_task再启动
    std::packaged_task<int()> task(func);
    auto future_result = task.get_future();
    std::thread t1(std::move(task));
    cout<<func()<<endl;

    t1.join();
    return 0;

}