#include <iostream>

// private 继承，一定程度上等效复合效果。与复合不同的是，private继承能够使用protected成员以及重载虚函数。

class Base
{
private:
    /* data */
public:
    Base(/* args */);
    void printfFunc(){
        std::cout << __FUNCTION__ << std::endl;
    }


    virtual void printfClass(){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~Base();

protected:
    void pritfLine(){
        std::cout << __LINE__ << std::endl;
    }
};

Base::Base(/* args */)
{
}

Base::~Base()
{
}


class Inherit : private Base
{
private:
    // 虚函数重载
    virtual void printfClass(){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
public:
    Inherit(/* args */);
    ~Inherit();
    void printfFuncAll(){
        this->printfFunc();
        this->pritfLine();
        this->printfClass();
    }
};

Inherit::Inherit(/* args */)
{
}

Inherit::~Inherit()
{
}

int main(int argc, char const *argv[])
{
    Inherit temp;
    temp.printfFuncAll();
    return 0;
}
