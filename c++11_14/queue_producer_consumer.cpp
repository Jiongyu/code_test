#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <chrono>

#define LOOP_TIMES (10000)

std::queue<int>g_queue;
std::condition_variable g_cv;
std::mutex g_mutex;

std::atomic<bool> g_flag(false); // 强行保证发送处理顺序

void producer(int arg)
{
    for(int i = 0; i < LOOP_TIMES; i++)
    {
        while (g_flag.load());
        
        std::unique_lock<std::mutex>lock(g_mutex);
        g_queue.push(i);
        std::cout << "queue push: " << i <<std::endl; 
        g_cv.notify_one();
        g_flag.store(true);
        lock.unlock();
        //std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}  

void consumer(int arg)
{
    for(int i = 0; i < LOOP_TIMES; i++)
    {
        std::unique_lock<std::mutex>lock(g_mutex);
        while (g_queue.empty()) // 避免虚假唤醒
            g_cv.wait(lock);
        std::cout << "queue get: " << g_queue.front() <<std::endl;
        g_queue.pop();
        g_flag.store(false);
        lock.unlock();
        //std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}  

template<typename T>
class Queue{

public:
    Queue():flag_(false), queue_(std::queue<T>()), queueMaxSize_(100){};
    ~Queue(){};
    void setQueueSize(int size);
    int push(T &data);
    T front();
    bool empty();
    int pop();

private:
    std::queue<T> queue_;
    std::condition_variable cv_;
    std::mutex mutex_;
    std::atomic<bool> flag_;
    std::atomic<int> queueMaxSize_;
};

template<typename T>
int Queue<T>::push(T &data)
{
    std::unique_lock<std::mutex>lock(g_mutex);
    if(queue_.size() < queueMaxSize_.load())
    {
        queue_.push(data);
        cv_.notify_all();
        return 0;
    }
    return -1;
}

template<typename T>
void Queue<T>::setQueueSize(int size)
{
    queueMaxSize_.store(size);
}


template<typename T>
T Queue<T>::front()
{
    std::unique_lock<std::mutex>lock(g_mutex);
    while (queue_.empty())
        cv_.wait(lock);   
     return queue_.front(); 
}

template<typename T>
int Queue<T>::pop()
{
    std::unique_lock<std::mutex>lock(g_mutex);
    while (queue_.empty()) // 避免虚假唤醒
        cv_.wait(lock);
    queue_.pop();
    return 0;
}

template<typename T>
bool Queue<T>::empty()
{
    std::unique_lock<std::mutex>lock(g_mutex);
    return queue_.empty();
}

Queue<int>g_queueTest;


void thread1(void)
{
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < LOOP_TIMES; i++)
    {
        while(g_queueTest.push(i));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    std::cout << "push time: " << time.count() << " milli." << std::endl;
}

void thread2(void)
{
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < LOOP_TIMES; i++)
    {
        std::cout << "get: " << g_queueTest.front() << std::endl;
        g_queueTest.pop();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    //std::cout << "pop time: " << time.count() << " milli." << std::endl;
}

int main(int argc, char const *argv[])
{

#if 0
    std::thread t1, t2;
    t1 = std::thread(producer, 1);
    t2 = std::thread(consumer, 2);

    t1.join();
    t2.join();
#else

    std::thread t1, t2;
    t1 = std::thread(thread1);
    t2 = std::thread(thread2);

    t1.join();
    t2.join();

#endif 
    return 0;
}
