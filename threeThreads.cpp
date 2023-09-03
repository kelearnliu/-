#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

std::mutex mtx;
std::condition_variable cv;
//bool flag{false};
int flag=0;
const int mod=3;
// 这里使用的代码必须都是notify_all 否则如果唤起的线程不满足要求的话就会一直阻塞下去
void printA()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        // flag=0时打印A 否则阻塞在这里
        cv.wait(lock,[]{return flag==0;});
        std::cout<<"A"<<std::endl;
        flag=(flag+1)%mod;
        std::this_thread::sleep_for(std::chrono::seconds (1));
        cv.notify_all();
    }
}
void printB()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        // flag=0时打印A 否则阻塞在这里
        cv.wait(lock,[]{return flag==1;});
        std::cout<<"B"<<std::endl;
        flag=(flag+1)%mod;
        std::this_thread::sleep_for(std::chrono::seconds (1));
        cv.notify_all();
    }
}

void printC()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        // flag=0时打印A 否则阻塞在这里
        cv.wait(lock,[]{return flag==2;});
        std::cout<<"C"<<std::endl;
        flag=(flag+1)%mod;
        std::this_thread::sleep_for(std::chrono::seconds (1));
        cv.notify_all();
    }
}
int main()
{
    std::thread t1(printA);
    std::thread t2(printB);
    std::thread t3(printC);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}