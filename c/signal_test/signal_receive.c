/**
 * @file signal_receive.c
 * @author your name (you@domain.com)
 * @brief  信号可靠性实验。 对比可靠信号，不可靠信号
 *         发送端，持续发送，对比发送次数与信号处理函数执行次数
 * @version 0.1
 * @date 2021-10-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

static int sig_cnt[NSIG];
static volatile sig_atomic_t get_SIGINT = 0;
void handler(int signo)
{
    if(signo == SIGINT)
        get_SIGINT = 1;
    else
        sig_cnt[signo]++;
} 

int main(int argc,char* argv[])
{
    int i = 0;
    sigset_t blockall_mask ;
    sigset_t empty_mask ;
    printf("%s:PID is %d\n",argv[0],getpid());

    for(i = 1; i < NSIG; i++)
    {
        if(i == SIGKILL || i == SIGSTOP || i== 32 || i== 33)
            continue;

        if(signal(i,&handler) == SIG_ERR)
        {
            fprintf(stderr,"signal for signo(%d) failed (%s)\n",
            i,strerror(errno));
        }
    }

    if(argc > 1)
    {
        int sleep_time = atoi(argv[1]);
        sigfillset(&blockall_mask);
        if(sigprocmask(SIG_SETMASK, &blockall_mask,NULL) == -1)
        {
            fprintf(stderr,"setprocmask to block all signal failed(%s)\n",
            strerror(errno));
            return -2;
        }
        printf("I will sleep %d second\n",sleep_time);
        sleep(sleep_time);
        sigemptyset(&empty_mask);
        if(sigprocmask(SIG_SETMASK, &empty_mask,NULL) == -1)
        {
            fprintf(stderr,"setprocmask to release all signal failed(%s)\n", strerror(errno));
            return -3;
        }
    }

    while(!get_SIGINT)
        continue ;

    printf("%-10s%-10s\n","signo","times");
    printf("------------------------\n");
    for(i = 1; i < NSIG ; i++)
    {
        if(sig_cnt[i] != 0 )
        {
            printf("%-10d%-10d\n",i,sig_cnt[i]);
        }
    }
    return 0;
}