#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

std::mutex mtx;
std::condition_variable cv;
bool flag{false};

void printA()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        // flag=0时打印A 否则阻塞在这里
        cv.wait(lock,[]{return flag==0;});
        std::cout<<"A"<<std::endl;
        flag=!flag;
        std::this_thread::sleep_for(std::chrono::seconds (1));
        cv.notify_one();
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
        flag=!flag;
        std::this_thread::sleep_for(std::chrono::seconds (1));
        cv.notify_one();
    }
}

int main()
{
    std::thread t1(printA);
    std::thread t2(printB);
    t1.join();
    t2.join();
    return 0;
}