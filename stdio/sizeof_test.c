#include<stdio.h>

int main(int argc, char const *argv[])
{
    int a = 10;
    int *p;

    // int apple = sizeof(int) * *p;

    // printf("%d \n", apple);

    // int b;
    // b = 1,2;
    // printf("%d \n", b); // 短错误


    int b, c = 1, d = 2;
    b = c = d;
    printf("%d,%d,%d \n", b,c,d);
    

    int x = 1, y = 2;
    int z = y+++x;
    printf("%d,%d,%d\n",x,y,z);


    char (*j)[20];
    printf("j: %d\n", sizeof(*j));
    char *i[20];
    printf("i: %d\n", sizeof(i));

    return 0;
}
