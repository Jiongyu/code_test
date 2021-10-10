#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

static int sig_cnt[NSIG];
static int number= 0;
int sigorder[128]= {0};

// gcc -o sigaction_delivery_order -DUSE_SIGACTION signal_delivery_order.c

#define MSG "#%d:receiver signal %d\n"

void handler(int signo)
{
    /*此处最好判断一下
    number的值，不要超出数组的长度
    */
    sigorder[number++] = signo;
}

int main(int argc,char* argv[])
{
    int i = 0;
    int k = 0;
    sigset_t blockall_mask;
    sigset_t pending_mask;
    sigset_t empty_mask;
    struct sigaction sa;

    sigfillset(&blockall_mask);
#ifdef USE_SIGACTION
    sa.sa_handler = handler;
    sa.sa_mask = blockall_mask ;
    sa.sa_flags = SA_RESTART ;
#endif
    printf("%s:PID is %d\n",argv[0],getpid());

    for(i = 1; i < NSIG; i++)
    {
        if(i == SIGKILL || i == SIGSTOP)
        continue;
    #ifdef USE_SIGACTION
        if(sigaction(i,&sa, NULL)!=0)
    #else
        if(signal(i,handler)== SIG_ERR)
    #endif
        {
            fprintf(stderr,"sigaction for signo(%d) failed (%s)\n",i, strerror(errno));
            // return -1;
        }
    }

    int sleep_time = atoi(argv[1]);
    if(sigprocmask(SIG_SETMASK,&blockall_mask,NULL) == -1)
    {
        fprintf(stderr,"setprocmask to block all signal failed(%s)\n",strerror(errno));
        return -2;
    }

    printf("I will sleep %d second\n",sleep_time);
    sleep(sleep_time);
    sigemptyset(&empty_mask);
    if(sigprocmask(SIG_SETMASK,&empty_mask,NULL) == -1)
    {
        fprintf(stderr,"setprocmask to release all signal failed(%s)\n",strerror(errno));
        return -3;
    }
    sleep(3);
    for(i = 0 ; i< number ; i++)
    {
        if(sigorder[i] != 0)
        {
            printf("#%d: signo=%d\n",i,sigorder[i]);
        }   
    }
    return 0;
}