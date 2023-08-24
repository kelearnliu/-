#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
int counter=0;
void increment()
{
    for(int i=0;i<500;i++)
    {
        std::unique_lock<std::mutex> lock(mtx);
        counter++;
        std::cout<<"thread_id:"<<std::this_thread::get_id()<<"\t";
        std::cout<<"p_id:"<<static_cast<pid_t>(getpid())<<"\t";
        std::cout<<"counter:"<<counter<<std::endl;
    }
    cv.notify_one();
}
int main() {
    std::thread thread1(increment);
    std::thread thread2(increment);

    std::cout<<"main:"<<getpid()<<"\t"<<"main thread:"<<std::this_thread::get_id()<<std::endl;
    {
        // lock 是一个已经锁住的互斥锁，cv.wait() 会在等待期间解锁这个互斥锁，允许其他线程访问被保护的资源。
        std::unique_lock<std::mutex> lock(mtx);
        // 后面返回的是true，函数返回不等待  返回的是false 释放锁 继续等待
        cv.wait(lock,[](){return counter==1000;});
    }
    thread1.join();
    thread2.join();
    return 0;
}
