#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>

//demo
std::mutex mtx_syn;
std::condition_variable cv_syn;
std::condition_variable cv_syn_1;
bool ready = false;
//线程A
void threadA(int id) 
{
    while (1)
    {
        std::unique_lock<std::mutex> lck(mtx_syn);
        while (!ready)
        {
            cv_syn.wait(lck);
        }
        // ...
        std::cout << "thread " << id << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cv_syn.notify_all();   // 唤醒所有等待线程：B和C，B和C将会竞争锁
        cv_syn.wait(lck);
    }

}

// 线程B
void threadB(int id) 
{
    while (1)
    {
        //新创建的 unique_lock 对象管理 Mutex 对象 m，并尝试调用 m.lock() 对 Mutex 对象进行上锁，如果此时另外某个 unique_lock 对象已经管理了该 Mutex 对象 m，则当前线程将会被阻塞
        std::unique_lock<std::mutex> lck(mtx_syn);
        while (!ready)
        {
            cv_syn.wait(lck);
        }
        // ...
        std::cout << "thread " << id << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cv_syn.notify_all();    // 唤醒所有等待线程：A和C，它们将会竞争锁
        cv_syn.wait(lck);
    }
}

// 线程C
void threadC(int id) 
{
    while (1)
    {
        std::unique_lock<std::mutex> lck(mtx_syn);
        while (!ready) cv_syn.wait(lck);
        // ...
        std::cout << "thread " << id << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(2));
        cv_syn.notify_all();    // 唤醒所有等待线程：A和B，它们将会竞争锁
        cv_syn.wait(lck);
    }
}

void threadD(int id) 
{
    while (1)
    {
        std::unique_lock<std::mutex> lck(mtx_syn);
        while (!ready) cv_syn.wait(lck);
        // ...
        std::cout << "thread " << id << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cv_syn.notify_all();    // 唤醒所有等待线程：A和B，它们将会竞争锁
        cv_syn.wait(lck);
    }
}

void threadE(int id) 
{
    while (1)
    {
        std::unique_lock<std::mutex> lck(mtx_syn);
        while (!ready) cv_syn.wait(lck);
        // ...
        std::cout << "thread " << id << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cv_syn.notify_all();    // 唤醒所有等待线程：A和B，它们将会竞争锁
        cv_syn.wait(lck);
    }
}


void go()
{
    std::unique_lock<std::mutex> lck(mtx_syn);
    ready = true;
    cv_syn.notify_one();    // 唤醒等待线程中的一个线程
}

int main()
{
    //线程同步
    std::thread threads[5];
    threads[0] = std::thread(threadA, 0);
    threads[1] = std::thread(threadB, 1);
    threads[2] = std::thread(threadC, 2);  
    threads[3] = std::thread(threadD, 3);  
    threads[4] = std::thread(threadE, 4);  

    std::cout << "5 threads ready to race...\n";
    go();                       // go!

    for (auto& th : threads) th.join();
}