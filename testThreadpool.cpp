#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <memory>

typedef std::function<void()> Task;
class Threadpool{
public:
    static Threadpool& GetInstance()
    {
        static Threadpool pool;
        return pool;
    }
    Threadpool(size_t threadNum=8):pool(std::make_shared<Pool>())
    {
        for(size_t i=0;i<threadNum;i++)
        {
            pool->threads.emplace_back(
                    [&]{
                        while(true){
                        std::unique_lock<std::mutex> lock(pool->mtx);

                        // case1 线程池关闭 且 任务为空 直接返回
                        if(pool->isClose && pool->tasks.empty())
                            return;

                        // case2 线程池没有关闭 且 还有任务才继续执行
                        // 所以这里用这个事件的反向时间进行阻塞
                        pool->cv.wait(lock,[&]{
                            return pool->isClose || !pool->tasks.empty();
                        });

                        // 用这个线程处理当前任务队列中的任务
                        Task task(std::move(pool->tasks.front()));
                        pool->tasks.pop();
                        lock.unlock();
                        task();

                        }
                    }
                    );
        }
    }

    template<class F, class... Args>
    void AddTasks(F&& f, Args&&... args)
    {
        // 定义一个task
        Task task= std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(pool->mtx);
            pool->tasks.emplace(std::move(task));
        }
        pool->cv.notify_one();

    }
    ~Threadpool()
    {
        {
            std::unique_lock<std::mutex> lock(pool->mtx);
            pool->isClose=true;
        }
        // 这里为什么要唤醒线程
        pool->cv.notify_all();
        // 这里一定要使用引用 否则报错
        for(auto& t:pool->threads)
            t.join();
    }
public:
    struct Pool{
        std::vector<std::thread> threads;
        std::queue<Task> tasks;

        std::mutex mtx;
        std::condition_variable cv;
        bool isClose;
    };
    std::shared_ptr<Pool> pool;
};


int main()
{
//    Threadpool pool = Threadpool::GetInstance();
    Threadpool pool(3);
    for(int i=0;i<20;i++)
    {
        pool.AddTasks([i]{
            std::cout<<"task: "<<i<<" is running!"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout<<"task: "<<i<<" is done!"<<std::endl;
        });
    }
    return 0;
}