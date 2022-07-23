#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h> 
#include <poll.h>
#include <time.h>

#include "noblockIo.h"


int main(int argc, char *argv[])
{
    int ret;
    int fd;
    struct pollfd pfds;
    struct timespec local_time;

    // printf(DEV_PATH);
    fd = open(DEV_PATH, O_RDWR | O_NONBLOCK);
    if(fd < 0)
    {
        PINFO("can`t open device path: [%s]\n", DEV_PATH);
        return EXIT_FAILURE;
    }

    pfds.fd = fd;
    pfds.events =  POLLIN | POLLRDNORM;
    pfds.revents = 0;

    while (1)
    {
        ret = poll(&pfds, 1, -1);
        if(ret < 0)
        {
            PINFO("poll error");
            return EXIT_FAILURE;
        }
        if(pfds.revents & POLLIN)   // 有数据可读
        {
            char buf[20];
            ret = read(pfds.fd, buf, sizeof(buf));
            clock_gettime(CLOCK_MONOTONIC, &local_time);
            PINFO("[%ld]:[%s]\n", local_time.tv_sec, buf);
            pfds.revents |= ~POLLIN;
        }
        sleep(5);
    }
    
    close(fd);
    return EXIT_SUCCESS;
}
