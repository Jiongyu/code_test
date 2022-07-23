#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h> 

#include "ioControlDriver.h"

int main(int argc, char *argv[])
{
    int fd;
    unsigned int cmd;
    int ret;
    int arg = 0;
    unsigned char str[10];
    char* temp_p;
    
    // printf(DEV_PATH);
    fd = open(DEV_PATH, O_RDWR);
    if(fd < 0)
    {
        PINFO("can`t open device path: [%s]\n", DEV_PATH);
        return EXIT_FAILURE;
    }

    while (1)
    {
        PINFO("please input command(1:open timer, 2: close timer, 3: set timer period, 4: close program):\n");
        ret = scanf("%d", &cmd);
        if(1 != ret){
            temp_p = fgets(str,sizeof(str), stdin);  // 防止輸入卡死
            continue;
        }

        if(1 == cmd)
        {
            cmd = OPEN_CMD;

        }else if (2 == cmd)
        {
            cmd = CLOSE_CMD;

        }else if (3 == cmd)
        {
            cmd = SETPERIOD_CMD;
            PINFO("input imter period:\n");
            ret = scanf("%d", &arg);
            if(1 != ret){
                temp_p = fgets(str,sizeof(str), stdin);  // 防止輸入卡死
                continue;
            }

        }else if(4 == cmd)
        {
            PINFO("see ya.\n");
            break;
        }else{
            continue;
        }
        
        ioctl(fd, cmd, arg);
    }
    
    close(fd);
    return EXIT_SUCCESS;
}
