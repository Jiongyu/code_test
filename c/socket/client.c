#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        printf("create socket error=%d(%s)!!!\n", errno, strerror(errno));
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12500);
    if (inet_pton(AF_INET, "192.168.1.9", &server_addr.sin_addr) <= 0)
    {
        printf("inet_pton error!!!\n");
        exit(1);
    }

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("socket connect error=%d(%s)!!!\n", errno, strerror(errno));
        exit(1);
    }
    printf("connect to server ok!\n");

    char msg[1024];
    int rbytes = read(client_fd, msg, sizeof(msg)-1);
    if (rbytes <= 0)
    {
        printf("read error=%d(%s)!!!\n", errno, strerror(errno));
        exit(1);
    }
    msg[rbytes] = 0; // null terminate
    printf("%s", msg);

    close(client_fd);

    return 0;
}