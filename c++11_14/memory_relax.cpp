#include <cassert>
#include <vector>
#include <thread>
#include <atomic>

// memory_order_relaxed k宽松模型:只适合原子操作，不需要同步的场景

std::atomic<int> count{0};
void f()
{
    for (int n = 0; n < 1000; ++n) {
        count.fetch_add(1, std::memory_order_relaxed);
    }
}
int main()
{
    std::thread threads[10];
    for (std::thread &thr: threads) {
        thr = std::thread(f);
    }
    for (auto &thr : threads) {
        thr.join();
    }
    assert(count.load() == 10000); // 永远不会失败
    return 0;
}