#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int fread_main(int argc, char const *argv[])
{
    printf("%s:\n", __FUNCTION__);
    int ret = 0;
    int read_size = 48;
    char *p = malloc(read_size);
    if(NULL == p) return -1;

    FILE *fd = NULL;
    fd = fopen("./data.log", "r");
    if(NULL == fd)
    {
        printf("fopen error\n");
        ret = -1;
        goto exit;
    }

    int read_times = 1;
    int size = fread(p, read_size, read_times, fd);
    if(read_times != size) 
    {
        printf("fread error.\n");
        goto exit;
        ret = -1;
    }
    printf("read data: %s\n", p);

exit:

    if(NULL != p)
        free(p);
    if(NULL != fd)
        fclose(fd);
    return ret;
}


int read_main(int argc, char const *argv[])
{
    printf("%s:\n", __FUNCTION__);
    int ret = 0;
    int read_size = 48;
    char *p = malloc(read_size);
    if(NULL == p) return -1;

    int fd = -1;
    fd = open("./data.log", S_IREAD);
    if(-1 == fd)
    {
        printf("fopen error\n");
        ret = -1;
        goto exit;
    }

    int size = read(fd, p, read_size);
    if(read_size != size) 
    {
        printf("fread error.\n");
        goto exit;
        ret = -1;
    }
    printf("read data: %s\n", p);

exit:

    if(NULL != p)
        free(p);
    if(-1 != fd)
        close(fd);
    return ret;
}



int main(int argc, char const *argv[])
{
    fread_main(0, NULL);
    read_main(0, NULL);
    return 0;
}

