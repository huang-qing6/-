#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT_ID 8800
#define SIZE 100

int main(){
    int sockfd, client_sockfd;
    struct sockaddr_in my_addr, client_addr;
    int addr_len;
    char buf[SIZE];

    // 1.socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // 2.bind
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT_ID);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));

    // recv/send
    addr_len = sizeof(struct sockaddr);
    while(1){
        printf("server is waiting for the connect:\n");
        recvfrom(sockfd, buf, SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);// 与TCP不同，不用recvfrom甚至不知道client来自    
        printf("recv from client: %s\n", buf);
    }

    close(sockfd);

    return 0;
}