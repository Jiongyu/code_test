#include <iostream>
#include <memory>

using namespace std;

void static_cast_test(){
    cout << endl << "static cast test." << endl;
    double a = 10.0;
    //　转换基本数据类型
    cout << "static cast before (size) : " << sizeof(a) << endl;
    int b = static_cast<int>(a);
    cout << "static cast after (size) : " << sizeof(b) << endl;

}

void const_cast_test(){
    cout << endl << "const cast test." << endl;
    int a = 10;
    int b = 10;
    const int *p = &a;
    // (*p) ++;  // error read only
    cout << "before const cast :" << *p << endl;

    int* c = const_cast<int *>(p);
    (*c) ++ ;
    cout << "after const cast :" << *c << endl;
}

class classA
{
private:
    /* data */
public:
    classA(/* args */){}
    virtual ~classA(){cout << "del class A" << endl;}
    virtual void func(){    cout << "class A func" << endl;}
};

class classB : public classA
{
private:
    /* data */
public:
    classB (/* args */){}
    ~classB (){cout << "del class B" << endl;}
    void func() {    cout << "class B func" << endl;}
};

void dynamic_cast_test(){
    cout << endl << "dynamic cast test." << endl;
    shared_ptr<classA> p1(new classA);
    p1->func();
    shared_ptr<classB> p2(new classB);
    p2->func();
    // 多态
    p1 = p2;
    p1->func();

    // 智能指针向下转换
    p2 = dynamic_pointer_cast<classB >(p1);
    p2->func();

    p1.reset();
    p2.reset();

    // 基类对象指向基类，转换失败
    classA *p3 = new classA;
    classB *p4 = nullptr; 

    // 转换失败
    if(p4 = dynamic_cast<classB *>(p3)){
        cout << "1.dynamic cast convert success." << endl;
        p4->func();
    }else
    {
        cout << "1. dynamic cast convert failed." << endl;
    }
    delete(p3);
    delete(p4);

    // 基类对象指向派生类，类型安全，转换成功
    classA *p7 = new classB;
    classB *p8 = nullptr; 
    
    // 转换成功
    if(p8 = dynamic_cast<classB *>(p7)){
        cout << "2.dynamic cast convert success." << endl;
        p8->func();
    }else
    {
        cout << "2. dynamic cast convert failed." << endl;
    }
    delete(p7);

    classA *p5 = new classA;
    classB *p6 = static_cast<classB *>(p5);
    // 无法转换
    p6->func();
    delete(p6);
}

int main(int argc, char const *argv[])
{
    static_cast_test();
    const_cast_test();
    dynamic_cast_test();
    return 0;
}
