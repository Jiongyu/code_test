#include <iostream>
#include <tuple>
#include <string>


std::tuple<int, double, std::string> someFun()
{
    std::tuple<int, double, std::string> result(7, 9.8, "test");
    return result;
}

int main(int argc, char const *argv[])
{
    // std::tuple<int, double, std::string> result = someFun();
    auto result = someFun();

    int val = std::get<0>(result);

    int dval = std::get<1>(result);

    std::string str = std::get<2>(result);
 
     // Print values
    std::cout << "int value = " << val << std::endl;
    std::cout << "double value = " << dval << std::endl;
    std::cout << "string value = " << str << std::endl;

    // Get 4th int value from tuple
    // Will cause compile error because this tuple
    // has only 3 elements
    //int iVal2 = std::get<4>(result); // Compile error
    // Wrong cast will force compile time error
    // Get first value from tuple in a string
    //std::string strVal2 = std::get<0>(result); // Compile error

    return 0;
}
