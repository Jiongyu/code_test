#include <stdio.h>

struct{
    char a[7];
    int b;
}__attribute__((aligned(8))) test_aligned_data_t;

struct test_data{
    char a[7];
    int b;
}test_data_t;

#define LIST_ENTRY (PTR, TYPE, MEMBER)  \
    ((TYPE*)((char*)(PTR) - (unsigned long)(&((TYPE*)0)->MEMBER)))

int main(int argc, char const *argv[])
{
    printf("pack size %ld\n", sizeof(test_aligned_data_t));
    printf("no pack size %ld\n", sizeof(test_data_t));

    struct test_data data = {0};
    printf("%p\n",&data);
    printf("%p\n", &data.a);
    printf("%p\n", &data.b);

    printf("%p\n",  ((struct test_data_t*)((char*)&data.b - (unsigned long)(&((struct test_data*)0)->b))));
    return 0;
}
