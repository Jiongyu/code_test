#include "thread_pool.h"

#include <stdio.h>
#include <unistd.h>

void* task_demo(void *arg)
{
    printf("work on task_demo {%d}.\n", *((int*)&arg));
    sleep(1);
    return NULL;
}

void thread_pool_demo()
{
    pool_t pool;
    pool_init(&pool, 5);
    for (size_t i = 0; i < 10; i++)
    {
        pool_add_task(&pool, task_demo, (void *)i);
    }
    sleep(10);
    pool_uninit(&(pool));
    
}

int main(int argc, char const *argv[])
{
    thread_pool_demo();
    return 0;
}
