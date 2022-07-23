#include <stdio.h>

struct{
    char a;
    int b;
    char c;
    int d;
}__attribute__((packed)) test_pack_data_t;

struct{
    char a;
    int b;
    char c;
    int d;
}test_data_t;

int main(int argc, char const *argv[])
{
    printf("pack size %ld\n", sizeof(test_pack_data_t));
    printf("no pack size %ld\n", sizeof(test_data_t));
    return 0;
}
