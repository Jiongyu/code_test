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

#define BACKLOG 16

int main()
{
    // socket
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0)
    {
        printf("create socket error=%d(%s)!!!\n", errno, strerror(errno));
        exit(1);
    }

    // bind
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(12500); // Port
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // IP
    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("socket bind error=%d(%s)!!!\n", errno, strerror(errno));
        exit(1);
    }

    // listen
    if (listen(listen_fd, BACKLOG) < 0)
    {
        printf("socket listen error=%d(%s)!!!\n", errno, strerror(errno));
        exit(1);
    }
    printf("server init ok, start to accept new connect...\n");

    int connIdx = 0;
    while (1)
    {
        // accept
        int client_fd = accept(listen_fd, NULL, NULL);
        if (client_fd < 0)
        {
            printf("socket accept error=%d(%s)!!!\n", errno, strerror(errno));
            exit(1);
        }
        printf("accept one new connect(%d)!!!\n", connIdx);

        static char msg[1024] = "";
        memset(msg, 0, sizeof(msg));
        snprintf(msg, sizeof(msg)-1, "connIdx=%d\n", connIdx);
        if (write(client_fd, msg, strlen(msg)) != strlen(msg))
        {
            printf("send msg to client error!!!\n");
            exit(1);
        }

        static char readBuf[1024] = "";
        memset(readBuf, 0, sizeof(readBuf));
        if (read(client_fd, readBuf, sizeof(readBuf)-1) != 0)
        {
            printf("read error!!! server close connection!!!\n");
            exit(1);
        }
        printf("server read return 0, client-FIN\n");
        close(client_fd);
        connIdx++;
    }

    // never
    close(listen_fd);

    return 0;
}