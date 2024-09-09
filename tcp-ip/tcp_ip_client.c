/*
 * 一个简单的tcpip客户端示例 
 *
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct socketaddr*)&addr, sizeof(addr));

    char *message = "Hello Server!";
    // 出现了broken pipe，很诡异
    send(sockfd, message, strlen(message), 0);

    char buffer[1024];
    recv(sockfd, buffer, sizeof(buffer), 0);

    close(sockfd);

    return 0;
}