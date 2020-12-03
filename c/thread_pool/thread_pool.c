#include "thread_pool.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void *pool_thread_server(void *arg);

void pool_init(pool_t *pool, int threadLimit)
{
    pool->threadLimit = threadLimit;
    pool->queueHead = NULL;
    pool->taskInQueue = 0;
    pool->destoryFlag = 0;
    // 创建存放线程id的空间
    pool->threadId = (pthread_t *)calloc(threadLimit, sizeof(pthread_t));

    pthread_mutex_init(&(pool->queueMutex), NULL);
    pthread_cond_init(&(pool->queueRead), NULL);

    // 创建线程
    for (size_t i = 0; i < threadLimit; ++ i)
    {
        pthread_create(&(pool->threadId[i]), NULL, pool_thread_server, pool);
    }

}

int pool_uninit(pool_t *pool)
{
    pthread_mutex_lock(&(pool->queueMutex));
    // 防止两次释放
    if(pool->destoryFlag)
    {
        return -1;
    }
    pool->destoryFlag = 1;
    pthread_mutex_unlock(&(pool->queueMutex));

    pthread_cond_broadcast(&(pool->queueRead));
    // 防止僵尸进程
    for (size_t i = 0; i < pool->threadLimit; ++ i)
    {
        pthread_join(pool->threadId[i], NULL);
    }
    free(pool->threadId);

    pthread_mutex_lock(&(pool->queueMutex));

    pool_task* head = NULL;
    while (pool->queueHead != NULL)
    {
        head = pool->queueHead;
        pool->queueHead = pool->queueHead->next;
        free(head);
    }
    pthread_mutex_unlock(&(pool->queueMutex));
    
    pthread_mutex_destroy(&(pool->queueMutex));
    pthread_cond_destroy(&(pool->queueRead));
    return 0;
}

/**
 * @brief 向线程池中添加一个任务
 * 
 * @param pool 线程次句柄
 * @param process 任务处理函数
 * @param arg 任务参数
 * @return int 成功 0, 失败非0
 */
static int __en_queue_task(pool_t *pool, poll_task_f process, void *arg)
{
    pthread_mutex_lock(&(pool->queueMutex));

    // 任务达到线程池数量上限
    if(pool->taskInQueue >= pool->threadLimit){
        printf("task in queue was readched to thread limit!\n");
        pthread_mutex_unlock(&(pool->queueMutex));
        return -1;
    }

    pool_task *insertTask = NULL;
    insertTask = (pool_task *)calloc(1, sizeof(pool_task));
    assert(insertTask != NULL);
    insertTask->process = process;
    insertTask->arg = arg;
    pool->taskInQueue ++;

    pool_task *taskFind = pool->queueHead;
    // 判断是否为队列第一个
    if(taskFind != NULL){
        while (taskFind->next != NULL)
        {
            taskFind = taskFind->next;
        }
        taskFind->next = insertTask;
    }else
    {
        pool->queueHead = insertTask;
    }

    pthread_cond_signal(&(pool->queueRead));
    pthread_mutex_unlock(&(pool->queueMutex));
    
    return 0;
}

/**
 * @brief 从线程池中取出一个任务
 * 
 * @param pool 线程池
 * @return pool_task* 任务句柄 
 */
static pool_task* __de_queue_pool(pool_t *pool)
{
    pthread_mutex_lock(&(pool->queueMutex));
    if(pool->destoryFlag)
    {
        pthread_mutex_unlock(&(pool->queueMutex));
        pthread_exit(NULL);
    }


    pool_task* task = NULL;

    if(pool->taskInQueue == 0)
    {
        // 如果线程池中任务数量等于零，且不销毁线程池，则处于阻塞状态
        while (pool->taskInQueue == 0 && (!pool->destoryFlag))
        {
            pthread_cond_wait(&(pool->queueRead), &(pool->queueMutex));    
        }
        
    }else
    {

        pool->taskInQueue --;
        task = pool->queueHead;
        pool->queueHead = pool->queueHead->next;
    }
    pthread_mutex_unlock(&(pool->queueMutex));
    
    return task;
}

int pool_add_task(pool_t *pool, poll_task_f process, void *arg){
    return ( __en_queue_task(pool, process, arg) );
}


/**
 * @brief 线程池服务程序
 * 
 * @param arg 线程池
 * @return void* 
 */
static void *pool_thread_server(void *arg)
{
    pool_t* pool = NULL;
    pool = (pool_t *)arg;

    while (1)
    {
        pool_task * task = NULL;
        task = __de_queue_pool(pool);
        if(task != NULL)
        {
            printf("thread is already to start %ld !\n", pthread_self());
            task->process(task->arg);
            free(task);
            task = NULL;
        }
    }
    pthread_exit(NULL);
    return NULL;
}