#include <iostream>
#include <vector>

class Test
{
private:
    int data_;
public:
    Test(/* args */);
    Test(const Test&);              /*拷贝构造函数*/
    Test &operator=(const Test&);   /*拷贝赋值构造*/
    Test (const Test&&) noexcept;   /*移动构造函数*/
    void set_data(int a);
    int get_data();
    ~Test();
};

Test::Test(/* args */)
{
    std::cout << "default constructor\n";
}

Test::Test(const Test& obj)
{
    std::cout << "resource copy constructor\n";

    /* 资源复制 */
    this->data_ = obj.data_;
}

Test& Test::operator=(const Test& obj)
{
    std::cout << "assign resource copy constructor\n";

    /* 资源复制 */
    this->data_ = obj.data_;
    return *this;
}

Test::Test(const Test&& obj) noexcept
{
    std::cout << "move resource copy\n";
    this->data_ = obj.data_;
}

Test::~Test()
{
    std::cout << "destructor~~~\n";
}

void Test::set_data(int a)
{
    data_ = a;
}

int Test::get_data()
{
    return this->data_;
}

int main(int argc, char const *argv[])
{
    Test a;
    a.set_data(100);
    Test b(a);  /*拷贝构造*/

    Test c;
    c.set_data(20);
    c = a;  /*赋值构造*/

    Test d = c; /*拷贝构造*/

    std::cout << "------------------\n";
    std::vector<Test> data;
    data.clear();
    Test e;
    e.set_data(50);
    data.push_back(e);  /*拷贝构造*/
    std::cout << "e: "<< e.get_data() << std::endl;
    data.push_back(std::move(e));
    std::cout << "e: "<< e.get_data() << std::endl;
    return 0;
}

