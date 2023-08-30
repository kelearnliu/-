#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <functional>
#include <thread>

class ThreadPool{
public:
    static ThreadPool& GetInstance()
    {
        static ThreadPool pool;
        return pool;
    }
    explicit ThreadPool(size_t threadNums=8):pool_(std::make_shared<Pool>()){
        for(size_t i=0;i<threadNums;i++)
        {
            pool_->threads.emplace_back([&]{
                while(true)
                {
                    std::unique_lock<std::mutex> lock(pool_->mtx);

                    if(pool_->isClosed && pool_->tasks.empty())
                    {
                        return;
                    }

                    pool_->cv.wait(lock,[this]{
                        return !pool_->tasks.empty() || pool_->isClosed;
                    });


                    // 执行
                    std::function<void()> task(std::move(pool_->tasks.front()));
                    pool_->tasks.pop();
                    // 已经过了临界区 尽快解锁
                    lock.unlock();
                    task();
                }
            });

        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(pool_->mtx);
            pool_->isClosed=true;
        }
        pool_->cv.notify_all();
        for(auto& t: pool_->threads)
        {
            t.join();
        }
    }

    template<class F,class... Args>
    void AddTask(F&& f, Args&&...args)
    {
        std::function<void()> task =
                std::bind(std::forward<F>(f),std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(pool_->mtx);
            pool_->tasks.emplace(std::move(task));
        }
        pool_->cv.notify_one();
    }
public:
    struct Pool{
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> tasks;

        std::mutex mtx;
        std::condition_variable cv;
        bool isClosed;
    };
    std::shared_ptr<Pool> pool_;
};
int main()
{
//    ThreadPool pool = ThreadPool::GetInstance();
    ThreadPool pool(5);
    for(int i=0;i<15;i++)
    {
        pool.AddTask([i]{
            std::cout<<"task "<<i<<" is running!"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout<<"task "<<i<<" is done!"<<std::endl;
        });
    }
    return 0;
}