#include <iostream> // std::cout, std::endl
#include <future>   // std::async, std::future
#include <chrono>   // seconds
using namespace std::chrono;

int main() {
    auto print = [](char c) {
        for (int i = 0; i < 10; i++) {
            std::cout << c;
            std::cout.flush();
            std::this_thread::sleep_for(milliseconds(1));
        }
    };
    // 不同launch策略的效果
    std::launch policies[] = {std::launch::async, std::launch::deferred};
    const char *names[] = {"async   ", "deferred"};
    for (int i = 0; i < sizeof(policies)/sizeof(policies[0]); i++) {
        std::cout << names[i] << ": ";
        std::cout.flush();
        auto f1 = std::async(policies[i], print, '+');
        auto f2 = std::async(policies[i], print, '-');
        f1.get();
        f2.get();
        std::cout << std::endl;
    }
    
    return 0;
}