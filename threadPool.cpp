#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <vector>
#include <functional>
#include <string>

class ThreadPool {
public:
    explicit ThreadPool(int numThreads): stop(false)
    {
        for(int i=0;i<numThreads;i++)
        {
            threads.emplace_back([this]
                {
                    while(1)
                    {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [this]
                    {
                     return !tasks.empty() || stop;
                    });

                    if(stop && tasks.empty())
                    {
                        return;
                    }
                    std::function<void()> task(std::move(tasks.front()));
                    tasks.pop();
                    lock.unlock();
                    task();
                }
                }
            );
        }
    }

    ~ThreadPool(){
        {
            // 这个作用域方便解锁
            std::unique_lock<std::mutex>lock(mtx);
            stop=true;
        }
        cv.notify_all();
        for(auto& t:threads)
        {
            t.join();
        }
    }

    template<class F, class... Args>
    void addTask(F && f, Args&&... args)
    {
        std::function<void()> task =
                std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(std::move(task));
        }
        cv.notify_one();
    }


public:
    // vector管理的是线程
    std::vector<std::thread> threads;
    // queue管理的是任务
    std::queue<std::function<void()>> tasks;

    std::mutex mtx;
    std::condition_variable cv;
    bool stop;
};


int main() {
    // 改进  单例模式 禁用拷贝构造和赋值
    ThreadPool pool(4);

    for(int i=0;i<10;i++)
    {
        pool.addTask([i]{
            std::cout<<"task : "<<i<<"is running!"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout<<"task : "<<i<<"is done"<<std::endl;
        });
    }
    return 0;
}
