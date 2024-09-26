#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT_ID 8800
#define SIZE 100

int main(){
    int sockfd, client_sockfd, i;
    struct sockaddr_in my_addr;
    struct sockaddr_in client_addr;
    int addr_len;
    char welcome[SIZE] = "Welcome to connect to moyuserver";

    // 1.socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 2.bind
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT_ID);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));

    // 3.listen
    listen(sockfd, 10);

    // 4.accept
    addr_len = sizeof(struct sockaddr);

    for(i = 0; i < 4; i++) // 总共16个进程初始化
        fork();

    while(1){
        printf("server is waiting for the connect:\n");
        client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);
        printf("client address = %s\n", inet_ntoa(client_addr.sin_addr)); // 二进制转换
    
        // 5.send
        send(client_sockfd, welcome, SIZE, 0);
        printf("Disconnect the client request.\n");

        // 6.close
        close(client_sockfd);
    }

    close(sockfd);

    return 0;
}