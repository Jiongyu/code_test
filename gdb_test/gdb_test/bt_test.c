#include<stdio.h>

int fun1(int a)
{
    return a + 1;
}

int fun2(int a)
{
    return fun1(a) + 2;
}

int fun3(int a)
{
    return fun2(a) + 3;
}
int main(int argc, char const *argv[])
{
    int flag = 1;
    printf("wait gdb\n");
    while(1 == flag);
    printf("jump wait gdb\n");
    
    printf("%d\n",fun3(fun3(10)));
    return 0;
}
