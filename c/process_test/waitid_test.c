#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    pid_t childpid;
    siginfo_t infop;
    pid = fork();

    if(pid < 0)
    {
        printf("error fork.\n");
    }
    else if(0 == pid)
    {
        childpid = getpid();
        printf("child process %d.\n", childpid);
        printf("child process sleep 15s.\n");
        sleep(100);
        exit(0);
    }
    else
    {
        printf("parent process %d.\n", getpid());

        printf("parent process sleep 5s.\n");
        // sleep(5);
        // WEXITED: 等待子进程终止事件
        // WSTOPPED: 等待信号暂停的子进程事件
        // WCONTINUED 等待先被暂停，但是被SIGCONT信号恢复执行的子进程。 

        pid = waitid(P_ALL, 0, &infop, WCONTINUED);
        if(pid < 0)
        {
            printf("wait child process error\n");
        }
        else
        {
            printf("parent process collect child process %d.\n", pid);
        }
    }
    return 0;
}

