/**
 * @file thread_join_cmp.c
 * @author your name (you@domain.com)
 * @brief  对比thread_join 和 no thread_join 的内存
 *              pmap threadID
 *              cat /proc/threadID/maps
 * 
 *              gcc -o pthread_no_join pthread_join_cmp.c -DNO_JOIN -lpthread
 *              gcc -o pthread_has_join pthread_join_cmp.c -lpthread
 * @version 0.1
 * @date 2021-10-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/types.h>
#define NR_THREAD 1
#define ERRBUF_LEN 4096

void* thread_work(void* param)
{
    int TID = syscall(SYS_gettid);
    printf("thread-%d IN \n",TID);
    printf("thread-%d pthread_self return %p \n",TID,(void*)pthread_self());
    sleep(60);
    printf("thread-%d EXIT \n",TID);
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid[NR_THREAD];
    pthread_t tid_2[NR_THREAD];
    char errbuf[ERRBUF_LEN];
    int i, ret;

    for(i = 0 ; i < NR_THREAD ; i++)
    {
        ret = pthread_create(&tid[i],NULL,thread_work,NULL);
        if(ret != 0)
        {
            fprintf(stderr,"create thread failed ,return %d (%s)\n",ret,strerror_r (ret,errbuf,sizeof(errbuf)));
        }
    }

    #ifdef NO_JOIN
        sleep(100);/*sleep是为了确保线程退出之后，再来重新创建线程*/
    #else
        printf("join thread Begin\n");
        for(i = 0 ; i < NR_THREAD; i++)
        {
            pthread_join(tid[i],NULL);
        }
    #endif

    for(i = 0 ; i < NR_THREAD ; i++)
    {
        ret = pthread_create(&tid_2[i],NULL,thread_work,NULL);
        if(ret != 0)
        {
            fprintf(stderr,"create thread failed ,return %d (%s)\n",ret,strerror_r(ret,errbuf,sizeof(errbuf)));
        }
    }

    sleep(1000);
    exit(0);
}