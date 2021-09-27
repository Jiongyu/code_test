#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

/* 等待所有进程结束 */
pid_t r_wait(int *stat_loc)
{
    int ret;
    while ((ret = wait(stat_loc)) == -1 &&  \
            (errno == EINTR)); // 信号中断继续wait
    
    return ret;
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
        printf("error fork.\n");
    }
    else if(0 == pid)
    {
        printf("child process %d.\n", getpid());
        exit(0);
    }
    else
    {
        printf("parent process %d.\n", getpid());

        pid = fork();
        if(pid < 0)
        {
            printf("error fork.\n");
        }
        else if(0 == pid)
        {
            printf("child process %d.\n", getpid());
            exit(0);
        }

        /* 子进程成为僵尸进程 */
        printf("parent process sleep 5s.\n");
        sleep(5);

        /*等待所有进程结束*/
        while ((pid = r_wait(NULL)) != -1)
        {
            if(pid < 0)
            {
                printf("wait child process error\n");
            }
            else
            {
                printf("parent process collect child process %d.\n", pid);
            }
            continue;
        }
        if(errno != ECHILD)
        {
            printf("wait all child process return error.\n");
        }
    }
    return 0;
}
