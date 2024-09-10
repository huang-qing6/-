#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/pthreadtypes.h>


int startup(unsigned short *port){
    int httpd = 0; // 服务器套接字
    int on = 1;
    struct sockaddr_in name;

    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if(httpd == -1)
        error_die("socket");
    memset(&name, 0, sizeof(name)); // 初始化服务器信息
    name.sin_family = AF_INET;
    name.sin_port = htons(*port); // 设置端口号
    name.sin_addr.s_addr = htonl(INADDR_ANY); // 设置IP地址为本地任意地址
    if(setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))){ // 设置套接字选项
        error_die("setsockopt failed");
    }
    if(bind(httpd, (struct sockaddr*)&name, sizeof(name)) < 0){
        erro_die("bind");
    }
    if(*port == 0){ // 如果端口号为0 ，动态分配一个
        socklen_t namelen = sizeof(name);
        if(getsockname(httpd, (struct sockaddr*)&name, &namelen) == -1)
            erro_die("getsockname");
        *port = ntohs(name.sin_port);// 更新端口号
    }
    if(listen(httpd, 5) < 0) // 监听开始
        erro_die("listen");

    return(httpd);
}

int main(){
    int server_sock = -1; // 服务器套接字
    unsigned short port = 4000; //监听端口号
    int client_sock = -1; // 客户端套接字
    struct sockaddr_in client_name; // 客户端地址信息
    socklen_t client_name_len = sizeof(client_name); // 客户端地址信息长度
    pthread_t newpthread; // 为了多线程而声名的新线程，但暂时无用

    server_sock = startup(&port);
    printf("httpd running on port %d\n", port);

    while (1)
    {
        client_sock = accept(server_sock,
        (struct sockaddr*)&client_name, 
        &client_name_len);
        if(client_sock == -1)
            error_die("accept");
        accept_request(client_sock);

        /* 多线程版本
        if(pthread_create(&newthread, NULL, (void*)accept_request, (void*)(__intptr_t)client_sock) != 0)
            perror("pthread_create");
        */
    }
    
    close(server_sock); // 关闭服务器套接字

    return 0;
}