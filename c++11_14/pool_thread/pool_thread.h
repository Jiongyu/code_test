#pragma once

#define TEST_

#include <vector>
#include <queue>
#include <atomic>
#include <future>
#include <thread>

#include <stdexcept>

#include <iostream>

namespace ThreadPool
{

#define THREAD_MAX_NUM 20

class threadpool
{

public:
    inline threadpool(unsigned short size = 4){ addthread(size); };
    ~threadpool();

    /**
     * @brief 提交一个任务，调用.get() 获取返回值等待执行完成。
     * 
     * @tparam F 函数名类型
     * @tparam Args 函数参数类型
     * @param f 函数名
     * @param args 函数参数
     * @return std::future<decltype(f(args...))> 
     */
    template<class F, class... Args> 
    auto commit(F&& f, Args&&... args)->std::future<decltype(f(args...))>
    {
        // std::cout << __FUNCTION__ << std::endl;

        if(!_run){
            throw  std::runtime_error("PoolThread is stopped!");
        }

        using retType = decltype(f(args...));

        // 函数参数，入口绑定
        auto task = std::make_shared<std::packaged_task<retType()>>(std::bind(
            std::forward<F>(f), std::forward<Args>(args)...
        ));

        std::future<retType> future = task->get_future();
        {
            std::unique_lock<std::mutex> lock { _mutex};
            _tasks.emplace([task]{
                (*task)();
            });
        }

        _cond.notify_one();
        return future;    
}

    /**
     * @brief Get the Idle Thread Numer object
     * 
     * @return int 
     */
    int getIdleThreadNumer() const {return _idleThreadNumber;}

    /**
     * @brief Get the Thread Number object
     * 
     * @return int 
     */
    int getThreadNumber() const {return _pool.size();}

private:

    /**
     * @brief 添加指定数量的线程
     * 
     * @param size 线程数量
     */
    void addthread(unsigned short size);

private:
    // 函数类型
    using _task = std::function<void()>;
    // 线程池      
    std::vector<std::thread> _pool;
    // 任务队列
    std::queue<_task> _tasks;
    // 任务锁
    std::mutex _mutex;
    // 条件阻塞
    std::condition_variable _cond;
    // 线程是否运行
    std::atomic<bool> _run{true};
    // 空闲线程数量
    std::atomic<int> _idleThreadNumber{THREAD_MAX_NUM};

#ifdef TEST_
    // 计算总执行线程次数
    std::atomic<int>_testNumber{0};
#endif

};

} // namespace ThreadPool
