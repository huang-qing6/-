#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT_ID 8800

int main(){
    int sockfd, client_sockfd;
    struct sockaddr_in my_addr;
    struct sockaddr_in client_addr;
    int addr_len;

    // 1.socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 2.bind
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htnos(PORT_ID);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));

    // 3.listen
    listen(sockfd, 10);

    // 4.accept
    addr_len = sizeof(struct sockaddr)
    while(1){
        printf("server is waiting for the connect:\n");
        client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);
        printf("client address = %s\n", inet_ntoa(client_addr.sin_addr));
    }

    return 0;
}