#include <iostream>
#include <memory>
#include <boost/scoped_ptr.hpp>
using namespace std;
using namespace boost;


void scoped_ptr_test(){
    scoped_ptr<int>p1 (new int);
    *p1.get() = 10;
    cout << "scoped ptr test:" << endl;
    cout << *p1 << endl; 

    //无法赋值，拷贝， 独立控制权
    // auto_ptr<int>p2 = p1;
    cout << endl;

}

void auto_ptr_test(){
    auto_ptr<int>p1 (new int);
    *p1.get() = 10;
    auto_ptr<int>p2(p1);
    cout << "auto ptr test:" << endl;
    // cout << *p1 << endl;  // 错误　只能指向一个对象
    cout << *p2 << endl;

    //赋值，拷贝
    auto_ptr<int>p3 = p2;
    cout << *p3 << endl;

    cout << endl;
}

void shared_ptr_test(){
    shared_ptr<int>p1 = make_shared<int>(10);
    *p1.get() = 10;
    cout << "shared ptr test:" << endl;
    shared_ptr<int>p2(p1);
    cout << *p1 << endl;  // 指向多个对象
    cout << *p2 << endl;
    // 协助shared_ptr 使用
    weak_ptr<int> p4 (p1);
    cout << "p1 refer number : " << p1.use_count() << endl;
    cout << "p2 refer number : " << p2.use_count() << endl;

    cout << "shared ptr refer number : " << p4.use_count() << endl;
    cout << "shared ptr refer number equal zero ? " << (p4.expired() ? "yes" : "no") << endl;
    // 获取一个shared_ptr
    shared_ptr<int>p5 =  p4.lock();
    cout << "weak_ptr lock value: " << *p5 << endl;


    // 清空 指针
    p5.reset();
    if(p5 == nullptr) cout << "p5 is nullptr" << endl;
    cout << endl;
}

void unique_ptr_test(){
    unique_ptr<int>p1 = make_unique<int>(10);
    *p1.get() = 10;
    cout << "unique ptr test:" << endl;
    cout << *p1 << endl;
    // unique_ptr<int>p2(p1); // 错误　只能指向一个对象
    // unique_ptr<int> p3;
    // p3 = p1;// 错误　只能指向一个对象
    cout << endl;
}


//  g++ smart_pointer.cpp -std=c++14

int main(int argc, char const *argv[])
{

    auto_ptr_test();
    scoped_ptr_test();
    shared_ptr_test();
    unique_ptr_test();
    return 0;
}
