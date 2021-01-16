#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

int main(int argc, char const *argv[])
{
    // vector 自动扩容， 扩大开销
    std::vector<int>data1;

    // array 固定大小
    constexpr int size_ = 4;
    std::array<int, size_>data2;

    std::cout<< data1.capacity() << std::endl;

    std::cout<< data2.size() << std::endl;

    data1.push_back(1);
    data1.push_back(1);
    data1.push_back(1);
    data1.push_back(1);
    data1.push_back(1);
    std::cout<< data1.capacity() << std::endl;

    data2.fill(1);
    for(auto i : data2){
        std::cout << i << " ";
    }
    std::cout << "\n";
    data2[1] = 2;
    for(auto i : data2){
        std::cout << i << " ";
    }
    std::cout << "\n";
    std::sort(data2.begin(), data2.end(), [](int a, int b){
        return a < b;
    });    
    for(auto i : data2){
        std::cout << i << " ";
    }

    return 0;
}
