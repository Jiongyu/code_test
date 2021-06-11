#include <iostream>

using namespace std;


// 这样定义的枚举实现了类型安全，首先他不能够被隐式的转换为整数，
// 同时也不能够将其与整数数字进行比较，更不可能对不同的枚举类型的枚举值进行比较。
// 枚举类型后面使用了冒号及类型关键字来指定枚举中枚举值的类型，这使得我们能够为枚举赋值（未指定时将默认使用 int）
enum class new_enum : unsigned int {
    value1,
    value2,
    value3 = 100,
    value4 = 100
};

// 希望获得枚举值的值时，将必须显式的进行类型转换，不过我们可以通过重载 << 这个算符来进行输出，
template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}


int main(int argc, char const *argv[])
{
    // 相同枚举值之间如果指定的值相同，那么可以进行比较：
    if (new_enum::value3 == new_enum::value4) {
        // 会输出
        std::cout << "new_enum::value3 == new_enum::value4" << std::endl;
    }

    // error
    if(new_enum::value3 == 100){
        
    }

    std::cout << new_enum::value3 << std::endl;

    return 0;
}
