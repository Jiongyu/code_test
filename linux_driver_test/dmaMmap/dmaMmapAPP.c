#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <unistd.h>

#include "dmaMmap.h"

int main(int argc, char const *argv[])
{
    int fd = -1;
    int ret = 0;
    char *mappedMem = NULL;

    fd = open(DEV_NAME, O_RDWR);
    if(0 > fd)
    {
        PINFO("open error %s\n", strerror(errno));
        ret = -1;
        goto exit;
    }

    mappedMem = mmap(NULL, MAX_BUFFER_SZIE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(mappedMem == MAP_FAILED)
    {   
        PINFO("mmap error %s\n", strerror(errno));
        ret = -1;
        goto exit;
    }
    PINFO("address: %p\n", mappedMem);
    
    /* 设置物理内存中的值 */
    memset(mappedMem, 0, 128);
    memset(mappedMem, 'f', 127);
    PINFO("data:%s\n", mappedMem);
    munmap(mappedMem, MAX_BUFFER_SZIE);
    mappedMem = NULL;

    /* 重新读取物理内存中的值 */
    mappedMem = mmap(NULL, MAX_BUFFER_SZIE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(mappedMem == MAP_FAILED)
    {   
        PINFO("mmap error %s\n", strerror(errno));
        ret = -1;
        goto exit;
    }
    PINFO("address: %p\n", mappedMem);
    PINFO("data:%s\n", mappedMem);

    ret = 0;
exit:
    if(MAP_FAILED != mappedMem)
        munmap(mappedMem, MAX_BUFFER_SZIE);
    if(0 > fd)
        close(fd);
    return ret;
}
