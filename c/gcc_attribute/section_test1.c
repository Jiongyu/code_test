#include <stdio.h>

/*
    gcc ./section_test1.c -T ./section_test1.lds 
*/

/*
    查看特定段:
    objdump  -t -j __start_init ./a.out    
*/

typedef int (*init_fn_t)(void);

/*标记为attribute__((used))的函数被标记在目标文件中，以避免链接器删除未使用的节。*/
#define USED __attribute__((used))
#define SECTION(x) __attribute__((section(x)))

#define SECTION_PREFIX "__start_init"
#define INIT_EXPORT(fn) \
    USED const init_fn_t __init##fn SECTION(SECTION_PREFIX) = fn

init_fn_t __init_start;
init_fn_t __init_end;


static int test_start(void)
{
    printf("test_start\n");
    return 0;
}
INIT_EXPORT(test_start);


static int test_start_1(void)
{
    printf("test_start_1\n");
    return 0;
}
INIT_EXPORT(test_start_1);

static int test_start_3(void)
{
    printf("test_start_3\n");
    return 0;
}
INIT_EXPORT(test_start_3);

static int test_start_2(void)
{
    printf("test_start_2\n");
    return 0;
}
INIT_EXPORT(test_start_2);

static int test_end(void)
{
    printf("test_end\n");
    return 0;
}
INIT_EXPORT(test_end);


int main(int argc, char const *argv[])
{
    const init_fn_t *fn_start_ptr;
    for(fn_start_ptr = &__init_start; fn_start_ptr < &__init_end; fn_start_ptr ++)
    {
        (*fn_start_ptr)();
    }
    return 0;
}
