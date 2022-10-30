#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
 
 
#define DEV_NAME        "/dev/dma_m2m_test"
#define MEM_CPY_NO_DMA	_IOW('L', 0x1210, int)
#define MEM_CPY_DMA	    _IOW('L', 0x1211, int)
 
 
int main(void)
{
    int fd = -1;
    int ret = -1;
    struct timeval start, end;

    fd = open(DEV_NAME, O_RDWR);
    if(fd < 0){
        printf("open fail !\n");
        exit(1);
    }

    gettimeofday(&start, NULL);
    ioctl(fd, MEM_CPY_NO_DMA, 0);
    gettimeofday(&end, NULL);
    printf("mem copy time comsume:%ld us\n", 1000000 *(end.tv_sec - start.tv_sec) +  end.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    ioctl(fd, MEM_CPY_DMA, 0);
    gettimeofday(&end, NULL);
    printf("dma copy time comsume:%ld us\n", 1000000 *(end.tv_sec - start.tv_sec) +  end.tv_usec - start.tv_usec);

    return 0;
}