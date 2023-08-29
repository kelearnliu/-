#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> que;
void Producer()
{
    for(int i=0;i<10;i++)
    {
        std::unique_lock<std::mutex> lock(mtx);
        que.push(i);
        std::cout<<"Produce : "<<i<<std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        cv.notify_one();
    }

}
void Consumer()
{
    while (1)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [](){return !que.empty();});
        int val = que.front();
        std::cout<<"Consume : "<<val<<std::endl;
        std::cout<<std::endl;
        que.pop();
    }

}
int main() {
    std::thread thread1(Producer);
    std::thread thread2(Consumer);

    thread1.join();
    thread2.join();
    return 0;
}
