
#include <stdio.h>

/*弱引用函数*/
#define __WEAKDEF __attribute__((weak))
/*
jony@jonyu-pc:/mnt/h/learn/ubuntu20/code_test/c/gcc_attribute$ gcc ./test_weak1.c 
jony@jonyu-pc:/mnt/h/learn/ubuntu20/code_test/c/gcc_attribute$ ./a.out 
test_weak:./test_weak1.c
jony@jonyu-pc:/mnt/h/learn/ubuntu20/code_test/c/gcc_attribute$ gcc ./test_weak1.c  ./test_weak2.c 
jony@jonyu-pc:/mnt/h/learn/ubuntu20/code_test/c/gcc_attribute$ ./a.out 
test_weak:./test_weak2.c
*/

__WEAKDEF void test_weak()
{
    printf("test_weak:%s\n", __FILE__);

}

int main(int argc, char const *argv[])
{
    test_weak();
    return 0;
}
