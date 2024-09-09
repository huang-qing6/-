/*
 * 一个简单的tcpip服务端示例 
 *
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main(){
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // 创建sockect
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // 绑定IP和端口
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY 特殊IP地址，通常值为0
    address.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听
    if(listen(server_fd, 3) < 0){
        perror("listen failed");
        exit(EXIT_FAILURE);        
    }

    if((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){
        perror("accept failed");
        exit(EXIT_FAILURE);   
    }

    // 发送和接收数据的代码可以在这里添加

    return 0;
}