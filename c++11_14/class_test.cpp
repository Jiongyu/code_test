#include <iostream>

class demo1
{
public:
    demo1(){};
    void print1(){std::cout << "demo1 print1\n";};
    ~demo1(){};


};

/* 默认私有继承*/
class demo2 : demo1
{
public:
     demo2(){};
    ~demo2(){};   
};

class demo3 : public demo1
{
public:
     demo3(){};
    ~demo3(){};   
};

int main(int argc, char const *argv[])
{
    demo2 demo;
    /* 默认私有继承无法访问 */
    // demo.print1();

    demo3 demo_;
    demo_.print1();   
    return 0;
}
