#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT_ID 8800
#define SIZE 100

void *func(void *);

struct sockaddr_in client_addr;
int client_sockfd;
char welcome[SIZE] = "Welcome to connect to moyuserver";

int main(){
    int sockfd;
    struct sockaddr_in my_addr;
    int addr_len;
    pthread_t pthread;
    

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

    while(1){
        printf("server is waiting for the connect:\n");
        client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);
        pthread_create(&pthread, NULL, func, NULL);
    }

    close(sockfd);

    return 0;
}

void *func(void *arg){
        printf("client address = %s\n", inet_ntoa(client_addr.sin_addr)); // 二进制转换
    
        // 5.send
        send(client_sockfd, welcome, SIZE, 0);
        printf("Disconnect the client request.\n");

        // 6.close
        close(client_sockfd);

        return NULL;
}