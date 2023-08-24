#include <iostream>
#include <atomic>
#include <thread>
#include <unistd.h>

std::atomic<int> counter(0);

void increment()
{
    for(int i=0;i<500;i++)
    {
        counter.fetch_add(1,std::memory_order_relaxed);


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
