#include "pool_thread.h"
namespace ThreadPool
{
    
threadpool::~threadpool()
{
    _run = false;
    _cond.notify_all();
    for(std::thread& thread : _pool )
    {
        if(thread.joinable()){
            thread.join();
        }
    }

#ifdef TEST_
    std::cout << "execute " << _testNumber << " threads!" << std::endl;
#endif
}

void threadpool::addthread(unsigned short size)
{
    for(; _pool.size() < THREAD_MAX_NUM && size > 0; --size)
    {
        _pool.emplace_back( [this]{
            while (_run)
            {
                _task task;

                /**
                 * @brief 等待直到有task
                 */
                {
                    std::unique_lock<std::mutex> lock { _mutex};
                    _cond.wait(lock, [this]{
                        return !_run || !_tasks.empty();
                    });

                    if(!_run && _tasks.empty()){
                        return;
                    }

                    task = std::move(_tasks.front());
                    _tasks.pop();
                }
                task();
#ifdef TEST_
                _testNumber ++;
#endif
                _idleThreadNumber ++;
            }
            
        });
        _idleThreadNumber --;

    }
}

} // namespace ThreadPool