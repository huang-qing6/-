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
    int sockfd, i;
    struct sockaddr_in server_addr;
    char buf[SIZE];
    if(argc < 2){
        printf("usage: client <server ip addr>\n");
        _exit(1);
    }
    // 1.socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // 2.connect
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_ID);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]); // 十进制转为二进制，用于IPV4转换
    
    for(i = 0; i < 10; i++){
        sprintf(buf, "%d", i);
        sendto(sockfd, buf, SIZE, 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
        printf("Client sends to server %s: %s\n", argv[1], buf);
        sleep(1);
    }
    close(sockfd);

    return 0;
}