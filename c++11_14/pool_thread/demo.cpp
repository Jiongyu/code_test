#include "./pool_thread.h"
#include <iostream>

void fun1(int a, int b)
{   
    std::cout << "this thread id: " << std::this_thread::get_id() << std::endl ;
    std::cout << a << "," << b << std::endl ;
    std::this_thread::sleep_for( std::chrono::seconds(a + b));

}

// 带返回值静态函数
static int fun2(int a)
{
    std::cout << "this thread id: " << std::this_thread::get_id() << std::endl ;
    std::this_thread::sleep_for( std::chrono::seconds(a % 5));
    return a + 1;
}

// 带返回值
struct fun3
{
    int operator()(int a){
        std::cout << "this thread id: " << std::this_thread::get_id() << std::endl ;
        std::this_thread::sleep_for( std::chrono::seconds(a % 5));
        return a + 1;
    }
};


int main(int argc, char const *argv[])
{
    unsigned short threadNumber = 100;
    ThreadPool::threadpool pool{threadNumber};


    for(int i = 0 ; i < threadNumber; ++ i)
    {
        pool.commit(fun1, i % 3,  i % 2);
    }
    std::future<int> dd = pool.commit(fun2, 1); 
    std::cout << dd.get() << std::endl;

    std::future<int> ff = pool.commit(fun3{}, 4); 
    std::cout << ff.get() << std::endl;

    

    return 0;
}
