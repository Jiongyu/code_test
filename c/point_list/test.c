#include<stdio.h>

#define MAX_LEN 20

int (*func[MAX_LEN])(int a);

int test(int a)
{
    printf("%d\n", a);
    return 0;
}


int main(int argc, char const *argv[])
{
    for(int i = 0; i < MAX_LEN; i++)
    {
        func[i] = test;
    }

    for(int i = 0; i < MAX_LEN; i++)
    {
        func[i](i);
    }
    printf("%d\n", sizeof(func) / sizeof(func[0]));
    return 0;
}
