#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

std::mutex mtx;
int counter=0;
std::thread::id tid;
void increment()
{
    for(int i=0;i<500;i++)
    {
        std::lock_guard<std::mutex> lg(mtx);
        std::cout<<"thread_id:"<<std::this_thread::get_id()<<"\t";
        if(tid != std::this_thread::get_id())  std::cout<<"CCCCCCCCCCCCCCCCCCCCCCCCCC"<<"\t";
        std::cout<<"p_id:"<<static_cast<pid_t>(getpid())<<"\t";
        tid=std::this_thread::get_id();
        counter++;
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
