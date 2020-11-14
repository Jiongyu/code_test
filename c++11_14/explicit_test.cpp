#include <iostream>

class Demo1
{
private:
    /* data */
public:
    Demo1(int data);
    ~Demo1();
};

Demo1::Demo1(int data)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << data << std::endl;

}

Demo1::~Demo1()
{
}


class Demo2
{
private:
    /* data */
public:
    // 防止隐身转换
    explicit Demo2(int data);
    ~Demo2();
};

Demo2::Demo2(int data)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << data << std::endl;
}

Demo2::~Demo2()
{
}


int main(int argc, char const *argv[])
{
    int data = 10;
    Demo1 temp1(data);
    Demo1 temp2 = data; // 隐身转换

    Demo2 temp3(data);
    // Demo2 temp4 = data; // explicit 禁止构造函数隐私转换

    return 0;
}

