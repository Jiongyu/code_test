// #include <stdio.h>

// int(*)() get_close_package()
// {
//     int cnt = 0;

//     int add_cnt()
//     {
//         cnt ++;
//         return cnt;
//     }

//     return add_cnt;
// }

// int main(int argc, char const *argv[])
// {
//     int a = 0;
//     int(*fun)() = get_close_package();

//     a = fun();
//     a = fun();
//     a = fun();
//     a = fun();
//     printf("cnt:%d\n", a);
//     return 0;
// }

#include <stdio.h>
void* caller() {
    int cnt = 0;
    void callee()
    {
        cnt++;
        printf("%d\n", cnt);
    }
    printf("%p\n", callee);
    return callee;
}
int main()
{
    void(*callee)(void) = caller();
    printf("%p\n", callee);
    (*callee)();
    return 0;
}
