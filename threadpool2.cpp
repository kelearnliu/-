//#include <vector>
//#include <queue>
//#include <mutex>
//#include <condition_variable>
//#include <iostream>
//#include <functional>
//#include <thread>
//
//class ThreadPool{
//public:
//    static ThreadPool& GetInstance()
//    {
//        static ThreadPool pool;
//        return pool;
//    }
//    explicit ThreadPool(size_t threadNums=8):pool_(std::make_shared<Pool>()){
//        for(size_t i=0;i<threadNums;i++)
//        {
//            pool_->threads.emplace_back([&]{
//                while(true)
//                {
//                    std::unique_lock<std::mutex> lock(pool_->mtx);
//
//                    if(pool_->isClosed && pool_->tasks.empty())
//                    {
//                        return;
//                    }
//
//                    // 只有在任务队列为空 且 线程池没关的情况下 才需要等待  后面的条件不为真时才等待
//                    pool_->cv.wait(lock,[this]{
//                        return !pool_->tasks.empty() || pool_->isClosed;
//                    });
//
//
//                    // 执行
//                    std::function<void()> task(std::move(pool_->tasks.front()));
//                    pool_->tasks.pop();
//                    // 已经过了临界区 尽快解锁
//                    lock.unlock();
//                    task();
//                }
//            });
//
//        }
//    }
//
//    ~ThreadPool()
//    {
//        {
//            std::unique_lock<std::mutex> lock(pool_->mtx);
//            pool_->isClosed=true;
//        }
//        pool_->cv.notify_all();
//        for(auto& t: pool_->threads)
//        {
//            t.join();
//        }
//    }
//
//    template<class F,class... Args>
//    void AddTask(F&& f, Args&&...args)
//    {
//        std::function<void()> task =
//                std::bind(std::forward<F>(f),std::forward<Args>(args)...);
//        {
//            std::unique_lock<std::mutex> lock(pool_->mtx);
//            pool_->tasks.emplace(std::move(task));
//        }
//        pool_->cv.notify_one();
//    }
//public:
//    struct Pool{
//        std::vector<std::thread> threads;
//        std::queue<std::function<void()>> tasks;
//
//        std::mutex mtx;
//        std::condition_variable cv;
//        bool isClosed;
//    };
//    std::shared_ptr<Pool> pool_;
//};
//int main()
//{
////    std::shared_ptr<ThreadPool> p;
////    ThreadPool pool = p->GetInstance();
//    ThreadPool pool(5);
//    for(int i=0;i<15;i++)
//    {
//        pool.AddTask([i]{
//            std::cout<<"task "<<i<<" is running!"<<std::endl;
//            std::this_thread::sleep_for(std::chrono::seconds(1));
//            std::cout<<"task "<<i<<" is done!"<<std::endl;
//        });
//    }
//    return 0;
//}

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector<int> customSort(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    // 创建一个映射表，将 arr2 中的元素与其索引关联起来
    std::unordered_map<int, int> indexMap;
    for (int i = 0; i < arr2.size(); ++i) {
        indexMap[arr2[i]] = i;
    }

    // 自定义排序函数，根据 arr2 中元素的索引排序
    auto customComparator = [&indexMap](int a, int b) {
        // 如果 a 或 b 不在 arr2 中，将其排在后面
        if (indexMap.find(a) == indexMap.end() && indexMap.find(b) == indexMap.end()) {
            return a < b; // 保持相对顺序不变
        } else if (indexMap.find(a) == indexMap.end()) {
            return false; // a 不在 arr2 中，排在后面
        } else if (indexMap.find(b) == indexMap.end()) {
            return true; // b 不在 arr2 中，排在后面
        } else {
            return indexMap[a] < indexMap[b]; // 根据 arr2 中的顺序比较
        }
    };

    // 使用自定义排序函数对 arr1 进行排序
    std::vector<int> sortedArr1(arr1);
    std::sort(sortedArr1.begin(), sortedArr1.end(), customComparator);

    return sortedArr1;
}

int main() {
    std::vector<int> arr1 = {2, 1, 3, 5, 4, 6};
    std::vector<int> arr2 = {1, 3, 5};

    std::vector<int> result = customSort(arr1, arr2);

    // 输出排序后的结果
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
