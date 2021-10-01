/**
 * @file record_sender_data.c
 * @author your name (you@domain.com)
 * @brief 记录信号发送端信息
 * @version 0.1
 * @date 2021-10-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void sig_handler(int signo,siginfo_t *info,void *context)
{
    printf("\nget signal:%d\n",signo);
    printf("signal number is %d\n",info->si_signo);
    printf("pid=%d\n",info->si_pid);
    printf("sigval = %d\n",info->si_value.sival_int);
}

int main(void)
{
    struct sigaction new_action;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_sigaction = sig_handler;
    new_action.sa_flags |= SA_SIGINFO | SA_RESTART;

    if(sigaction(36,&new_action,NULL)==-1){
        printf("set signal process mode\n");
        exit(1);
    }

    while(1)
        pause();

    printf("Done\n");

    exit(0);
}