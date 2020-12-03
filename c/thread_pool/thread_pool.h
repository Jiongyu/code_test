#ifndef THREAD_POLL_H__
#define THREAD_POLL_H__

#include <pthread.h>

// 任务回调函数
typedef void* (*poll_task_f)(void *arg);

// 任务句柄
typedef struct _task
{
    poll_task_f process;    // 回调函数
    void *arg;
    struct _task *next;

} pool_task;

// 线程池句柄
typedef struct
{
    pthread_t *threadId;        // 线程号
    int threadLimit;        // 线程数量限制
    int destoryFlag;        // 判断线程是否销毁 0销毁 1不销毁
    pool_task *queueHead;       // 链表结构
	int taskInQueue;	    // 当前等待队列的任务数目
    pthread_mutex_t queueMutex; // 互斥锁
    pthread_cond_t  queueRead;  // 条件变量
} pool_t;

/**
 * @brief 初始化线程池并创建线程
 * 
 * @param pool 线程池句柄
 * @param threadLimit 线程数量限制
 */
void pool_init(pool_t *pool, int threadLimit);

/**
 * @brief 销毁线程池，等待队列中的任务不会被执行
 * 
 * @param pool 线程池句柄
 * @return int 成功 0, 失败非0
 */
int pool_uninit(pool_t *pool);

/**
 * @brief 向线程池中添加一个任务
 * 
 * @param pool 线程次句柄
 * @param process 任务处理函数
 * @param arg 任务参数
 * @return int 成功 0, 失败非0
 */
int pool_add_task(pool_t *pool, poll_task_f process, void *arg);

#endif