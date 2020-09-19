#include <iostream>

/**
 * @brief C++11 提供了 constexpr 让用户显式的声明函数或对象构造函数在编译器会成为常数，
 *          这个关键字明确的告诉编译器应该去验证 fibonacci 在编译器就应该是一个常数。
 * 
 * @param n 
 * @return constexpr int 
 */
constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1)+fibonacci(n-2);
}

/**
 * @brief 从 C++14 开始，constexptr 函数可以在内部使用局部变量、循环和分支等简单语句
 * 
 * @param n 
 * @return constexpr int 
 */
constexpr int fibonacci_2(const int n) {
    if(n == 1) return 1;
    if(n == 2) return 1;
    return fibonacci_2(n-1)+fibonacci_2(n-2);
}

int main() {
    
    int data[fibonacci(10)];
    std::cout << sizeof(data) / sizeof(data[0]) << std::endl;

    int data_2[fibonacci_2(10)];    //C++11 的标准下是不能够通过编译的
    std::cout << sizeof(data_2) / sizeof(data_2[0]) << std::endl;

    return 0;
}