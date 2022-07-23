#include <iostream>
#include <chrono>
using namespace std;

#define RUN_FUN(FUN, A, B, TIMES) \
do{ \
    for(int i = 0; i < TIMES; i++)  \
    {   \
        for(int j = 0; j < TIMES; j++)  \
        {   \
            for(int k = 0; k < TIMES; k++)  \
            {   \
                FUN(A[k], B[k]);  \
            }   \
        }   \ 
    }   \
}while(0)


int func1 (int a, int b)
{
    int c = a + b;
    int d = c + a + b;
    return d * c;
}

inline int func2 (int a, int b)
{
    int c = a + b;
    int d = c + a + b;
    return d * c;
}

int main(int argc, char const *argv[])
{
    int a[1000], b[1000];
    auto t0 = chrono::high_resolution_clock::now();
    RUN_FUN(func1, a, b, 1000);

    auto t1 = chrono::high_resolution_clock::now();
    RUN_FUN(func2, a, b, 1000);

    auto t2 = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> t0t1 = t1 - t0;
    chrono::duration<double, std::milli> t1t2 = t2 - t1;

    std::cout << "t1 - t0 " << t0t1.count() << " t2 - t1 " << t1t2.count() << std::endl;
    return 0;
}
