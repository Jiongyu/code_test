#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h> 
#include <signal.h>
#include <time.h>

#include "asynio.h"

static int fd = 0;
static char read_buff[20];
static struct timespec local_time;


static void signal_function(int arg)
{
    clock_gettime(CLOCK_MONOTONIC, &local_time);
    PINFO("[%ld] signal_function\n", local_time.tv_sec);
    int err = 0;
    err = read(fd, read_buff, sizeof(read_buff));
    if(err < 0){
        PINFO("error\n");
    }else{
        clock_gettime(CLOCK_MONOTONIC, &local_time);
        PINFO("[%ld]:[%s]\n", local_time.tv_sec, read_buff);
        
    }
}


int main(int argc, char *argv[])
{
    unsigned char cmd;
    int ret;
    int arg = 0;
    unsigned char str[10];
    char* temp_p;
    int flag;

    // printf(DEV_PATH);
    fd = open(DEV_PATH, O_RDWR | O_NONBLOCK);
    if(fd < 0)
    {
        PINFO("can`t open device path: [%s]\n", DEV_PATH);
        return EXIT_FAILURE;
    }

    signal(SIGIO, signal_function); // 绑定信号函数
    fcntl(fd, F_SETOWN, getpid());  // 设置当前进程接受SIGIO信号
    flag = fcntl(fd, F_GETFD);  // 获取当前进程状态
    fcntl(fd, F_SETFL, flag | FASYNC);  // 设置进程启用异步通知

    while (1)
    {
        PINFO("quit command(q):\n");
        ret = scanf("%c", &cmd);
        if(1 != ret){
            temp_p = fgets(str,sizeof(str), stdin);  // 防止輸入卡死
            continue;
        }

        if('q' == cmd){
            break;
        }
    }
    
    close(fd);
    return EXIT_SUCCESS;
}
