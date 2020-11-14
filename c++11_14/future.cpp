#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// g++ future.cpp -std=c++11 -pthread


/**
 * @brief 试想，如果我们的主线程 A 希望新开辟一个线程 B 去执行某个我们预期的任务，并返回我一个结果。
 * 而这时候，线程 A 可能正在忙其他的事情，无暇顾及 B 的结果，所以我们会很自然的希望能够在某个特定的
 * 时间获得线程 B 的结果。在 C++11 的 std::future 被引入之前，通常的做法是：创建一个线程A，
 * 在线程A里启动任务 B，当准备完毕后发送一个事件，并将结果保存在全局变量中。而主函数线程 A 里正在做
 * 其他的事情，当需要结果的时候，调用一个线程等待函数来获得执行的结果。
 * 而 C++11 提供的 std::future 简化了这个流程，可以用来获取异步任务的结果。
 * 自然地，我们很容易能够想象到把它作为一种简单的线程同步手段。
 */

// std::packaged_task 可以用来封装任何可以调用的目标，从而用于实现异步的调用。

int main()
{
    // 将一个返回值为7的 lambda 表达式封装到 task 中
    // std::packaged_task 的模板参数为要封装函数的类型
    std::packaged_task<int()> task([](){ 
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return 7;
    });
    // 获得 task 的 future
    std::future<int> result = task.get_future();    // 在一个线程中执行 task
    std::thread(std::move(task)).detach();    
    std::cout << "Waiting..." << std::endl;
    // result.wait();
    // 输出执行结果
    std::cout << "Done!" << std:: endl << "Result is " << result.get() << '\n';
    
    return 0;
}
