#include <iostream>
#include <vector>
#include <algorithm>

void printdata(const std::vector<int>&data)
{
    for(auto &i:data)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::for_each(data.begin(), data.end(), [](const int &i){std::cout << i <<" ";});
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    std::vector<int> data1 = {1,2,3,4,5};
    std::cout << "data1: " << &data1 << std::endl;
    printdata(data1);

    std::vector<int> data2 = data1;
    data1[0] = 10;
    std::cout << "data2: " << &data2 << std::endl;
    printdata(data2);

    std::vector<int> data3(data1);
    data1[0] = 20;
    std::cout << "data3: " << &data3 << std::endl;
    printdata(data3);

    return 0;
}
