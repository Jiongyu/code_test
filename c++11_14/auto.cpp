#include <vector>
#include <iostream>

// auto 还不能用于推导数组类型
// auto 不能用于函数传参，因此下面的做法是无法通过编译的（考虑重载的问题，我们应该使用模板）
// ecltype 关键字是为了解决 auto 关键字只能对变量进行类型推导的缺陷而出现的

/**
 * @brief C++11 还引入了一个叫做尾返回类型（trailing return type），利用 auto 关键字将返回类型后置
 *          
 * @tparam T 
 * @tparam U 
 * @param x 
 * @param y 
 * @return decltype(x+y) 
 */
template<typename T, typename U>
auto add(T x, U y) -> decltype(x+y) {
    return x+y;
}


// // c++ 14
// template<typename T, typename U>
// auto add(T x, U y){
//     return x+y;
// }

int main(int argc, char const *argv[])
{

    auto x = 1;
    auto y = 2;
    decltype(x+y) z;
    std::cout << "decltype : " << z << std::endl;
    std::cout << add(x, y) << std::endl;

    std::vector<int> data(10, 0);
    for(auto itr = data.begin(); itr != data.end(); ++ itr){
        std::cout << *itr << " ";
    }
    std::cout << std::endl;
    
    // 基于范围的for循环
    for(auto &itr:data){
        std::cout << itr << " ";
    }
    return 0;
}

