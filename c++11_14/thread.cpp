#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>

using namespace std;

mutex mtx;

void fun1(int number){
    cout << "fun1 :";
    for(auto i = 0; i < number; ++ i ){
        mtx.lock();
        cout <<  i << endl;
        mtx.unlock();
        this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    cout << endl;
}

void fun2(int number){
    cout << "fun2 :";
    for(auto i = 0; i < number; ++ i ){
        mtx.lock();
        cout <<  i << " ";
        mtx.unlock();
        this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    cout << endl;
}

void fun3(int number){
    // 函数返回自动释放mtx
    // lock_guard 范围锁
    lock_guard<mutex>loker(mtx);
    cout << "fun3 :";
    for(auto i = 0; i < number; ++ i ){
        cout <<  i << " ";
        this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    cout << endl;

}


int main(int argc, char const *argv[])
{
    thread thread1(fun1, 10);
    thread thread2(fun2, 10);
    thread thread3(fun3, 10);

    
    thread1.join();
    thread2.join();
    thread3.join();
    
    return 0;
}
