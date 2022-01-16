#include <sys/types.h>    
#include <sys/stat.h>    
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h> 
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd = 0;
    int read_index = 16;
    char data[64];
    int iRet = 0;
    fd = open("./fseek.txt", O_RDONLY);
    if(fd < 0)
    {
        printf("open error!.\n");
        return -1;
    }
    memset(data, 0, sizeof(data));

    iRet = read(fd, data, read_index);
    if(iRet != read_index)
    {
        printf("Read error!. iRet:%d\n", iRet);
        iRet = -1;
        goto exit;
    }

    printf("1. read data: %s\n", data);
    memset(data, 0, sizeof(data));

    iRet = read(fd, data, read_index);
    if(iRet != read_index)
    {
        printf("Read error!. iRet:%d\n", iRet);
        iRet = -1;
        goto exit;
    }
    printf("2. read data: %s\n", data);
    memset(data, 0, sizeof(data));

    /*  设置上次读写位置 */
    lseek(fd, read_index, SEEK_SET);

    iRet = read(fd, data, read_index);
    if(iRet != read_index)
    {
        printf("Read error!. iRet:%d\n", iRet);
        iRet = -1;
        goto exit;
    }
    printf("3. lseek read data: %s\n", data);
    memset(data, 0, sizeof(data));

    iRet = 0;
exit:
    close(fd);
    return iRet;
}
