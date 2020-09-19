#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
/**
 * @brief   std::condition_variable 是为了解决死锁而生的。当互斥操作不够用而引入的。比如，线程可能需要等待某个条件
 *          为真才能继续执行，而一个忙等待循环中可能会导致所有其他线程都无法进入临界区使得条件为真时，就会发生死锁。所以，
 *          condition_variable 实例被创建出现主要就是用于唤醒等待线程从而避免死锁。std::condition_variable的 
 *          notify_one() 用于唤醒一个线程；notify_all() 则是通知所有线程。 
 */
int main()
{
    // 生产者数量
    std::queue<int> produced_nums;
    // 互斥锁
    std::mutex m;
    // 条件变量
    std::condition_variable cond_var;
    // 结束标志
    bool done = false;
    // 通知标志
    bool notified = false;

    // 生产者线程
    std::thread producer([&]() {
        for (int i = 0; i < 5; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            // 创建互斥锁
            std::unique_lock<std::mutex> lock(m);
            std::cout << "producing " << i << '\n';
            produced_nums.push(i);
            notified = true;
            // 通知一个线程
            cond_var.notify_one();
        }   
        done = true;
        cond_var.notify_one();
    }); 

    // 消费者线程
    std::thread consumer([&]() {
        std::unique_lock<std::mutex> lock(m);
        while (!done) {
            while (!notified) {  // 循环避免虚假唤醒
                cond_var.wait(lock);
            }   
            while (!produced_nums.empty()) {
                std::cout << "consuming " << produced_nums.front() << '\n';
                produced_nums.pop();
            }   
            notified = false;
        }   
    }); 

    producer.join();
    consumer.join();
}