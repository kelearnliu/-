#include <iostream>
#include <thread>
#include <semaphore>
#include <atomic>

std::atomic<int> counter(0);
// 这里报错  不清楚原因  但是能够执行
std::counting_semaphore<1> sem(1);// 计数信号量，初始值为 1
void increment()
{
    for(int i=0;i<500;i++)
    {
        sem.acquire();  // 等待信号量可用
        ++counter;      // 自增操作
        sem.release();  // 释放信号量
        std::cout<<"thread_id:"<<std::this_thread::get_id()<<"\t";
        std::cout<<"p_id:"<<static_cast<pid_t>(getpid())<<"\t";
        std::cout<<"counter:"<<counter<<std::endl;
    }
}
int main() {
    std::thread thread1(increment);
    std::thread thread2(increment);
    std::cout<<"main:"<<getpid()<<"\t"<<"main thread:"<<std::this_thread::get_id()<<std::endl;
    thread1.join();
    thread2.join();
    return 0;
}
