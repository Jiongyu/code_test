#include <iostream>

class Base
{
private:
    int number;
public:
    Base(int data);
    ~Base();
    Base & operator = (const Base &obj1);
    friend Base operator- (const Base &obj1, const Base &obj2);
    Base & operator ++ (); // 前缀自增
    const Base & operator ++(int x); // 后缀自增

    void printfNumber(){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << this->number << std::endl;
    }

};

Base::Base(int data)
{
    // std::cout << __PRETTY_FUNCTION__ << std::endl;
    // std::cout << data << std::endl;

    this->number = data;
}

Base::~Base()
{
}

Base & Base::operator = (const Base &obj1){
    if(this != &obj1){
        this->number = obj1.number;
    }
    return *this;
}

Base operator - (const Base &obj1, const Base &obj2){
    // std::cout << __PRETTY_FUNCTION__ << std::endl;
    return Base(obj1.number - obj2.number);
}

Base & Base::operator ++ (){
    this->number ++;
    return *this;
}

const Base & Base::operator ++(int x){
    return *this;
}



int main(int argc, char const *argv[])
{
    Base temp1(10);
    temp1.printfNumber();
    Base temp2(30);
    temp2.printfNumber();
    temp1 = temp2;
    temp1.printfNumber();
    Base temp3(50);
    temp1 = (temp3 - temp1);
    temp1.printfNumber();

    // Base & operator ++ ();
    ++ temp1;
    temp1.printfNumber();

    temp1 ++;
    temp1.printfNumber();

    temp2 = temp1 ++;
    temp1.printfNumber();
    temp2.printfNumber();

    return 0;
}
