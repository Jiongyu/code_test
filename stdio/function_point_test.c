#include <stdio.h>

my_func_1(int data[2][3][5]){printf("my_func_1\n");};
my_func_2(int data[ ][3][5]){printf("my_func_2\n");};
my_func_3(int (*data)[3][5]){printf("my_func_3\n");};

int main(int argc, char const *argv[])
{
    int data[2][3][5];

    my_func_1(data);
    my_func_2(data);
    my_func_3(data);

    int(*p)[2][5] = data;
    my_func_1(p);
    my_func_2(p);
    my_func_3(p);

    int (*q)[2][3][5] = &data;
    my_func_1(q);
    my_func_2(q);
    my_func_3(q);

    return 0;
}
