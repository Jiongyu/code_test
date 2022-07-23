#include <thread>
#include <atomic>
#include <cassert>
#include <iostream>
 
std::atomic<bool> x = {false};
std::atomic<bool> y = {false};
std::atomic<int> z = {0};
 
void write_x()
{
    x.store(true, std::memory_order_seq_cst);
    std::cout << "x stored " << __FUNCTION__ <<std::endl;
}
 
void write_y()
{
    y.store(true, std::memory_order_seq_cst);
    std::cout << "y stored "<< __FUNCTION__ <<std::endl;
}
 
void read_x_then_y()
{
    while (!x.load(std::memory_order_seq_cst))
        ;
    std::cout << "x loades "<< __FUNCTION__ <<std::endl;
    if (y.load(std::memory_order_seq_cst)) {
        std::cout << "y loades "<< __FUNCTION__ <<std::endl;
        ++z;
    }
}
 
void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst))
        ;
        std::cout << "y loades "<< __FUNCTION__ <<std::endl;
    if (x.load(std::memory_order_seq_cst)) {
        std::cout << "x loades "<< __FUNCTION__ <<std::endl;
        ++z;
    }
}
 
int main()
{
    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join(); b.join(); c.join(); d.join();
    // 如果不使用顺序一致模型的话，则此处就可能触发断言
    assert(z.load() != 0);
}