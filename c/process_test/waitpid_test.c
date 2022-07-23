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
    pid = fork();
    if(pid < 0)
    {
        printf("error fork.\n");
    }
    else if(0 == pid)
    {
        childpid = getpid();
        sleep(15);
        printf("child process %d.\n", childpid);
        printf("child process sleep 15s.\n");
        sleep(15);
        exit(0);
    }
    else
    {
        printf("parent process %d.\n", getpid());

        printf("parent process sleep 5s.\n");
        sleep(5);
        // WUNTRACED: 子进程暂停立即返回
        // WCONTINUED 子进程继续立即返回
        // pid = waitpid(childpid, NULL, WUNTRACED | WCONTINUED);

        // 缺陷：无论用户是否关心相关子进程的终止事件，终止事件都会返回给用户,解决方案：waitid 
        pid = waitpid(childpid, NULL, 0);
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

