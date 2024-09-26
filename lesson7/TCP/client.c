#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT_ID 8800
#define SIZE 100

// client 192.168.130.140
int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in server_addr;
    char buf[SIZE];
    if(argc < 2){
        printf("usage: client <server ip addr>\n");
        _exit(1);
    }
    // 1.socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 2.connect
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_ID);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]); // 十进制转为二进制，用于IPV4转换
    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));

    // 3.recv
    recv(sockfd, buf, SIZE, 0);
    printf("recv:%s\n", buf);

    close(sockfd);

    return 0;
}