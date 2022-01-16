#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

int main(int argc, char const *argv[])
{
    std::vector<int>data = {1,2,3,4,5,6,6,7};

    std::sort(data.begin(), data.end(), std::greater<int>());

    std::for_each(data.begin(), data.end(), [](const int i){std::cout << i << " ";});
    std::cout << std::endl;

    std::plus<int> plus_func;
    std::negate<int> negate_func;
    std::cout << plus_func(2, negate_func(3)) << std::endl;
    return 0;
}

