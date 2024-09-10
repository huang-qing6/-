/*
 *   accept_request 实现
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// 从客户端接收请求，请求行占第一行，通过get_line来接收
int get_line(int sock, char* buf, int size){
    int i = 0;
    char c = '\0';
    int n;

    while ((i < size - 1) && (c != '\n'))
    {
        n = recv(sock, &c, 1, 0);

        if(n > 0){
            if(c == '\r'){
                n = recv(sock, &c, 1, MSG_PEEK);

                if((n > 0) && (c == '\n'))
                    recv(sock, &c, 1, 0);
                else    
                    c = '/n';                
            }
            buf[i] = c;
            i++;
        } else {
            c = '\n';
        }
    }
    buf[i] = '\0';

    return(i);
}

void unimplented(int client){
    char buf[1024];

    sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type:text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><HEAD><TILE>Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</TITLE></HEAD>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>HTTP request method not supported.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

void accept_request(int client_sock){
    // 假设这里打开了一个套接字sock
    char buffer[1024];
    int len = get_line(client_sock, buffer, sizeof(buffer));
    printf("Rec %s", buffer);

    // 接收第一行后需要判断GET还是POST方法
    // 如GET /idex.html HTTP....
    // 读出前面的方法后进行判别，假设保存方法在methond中
    char method[10];
    if(strcasecmp(method, "GET") && strcasecmp(method, "POST")){
        unimplented(client_sock); // 告诉客户端没这种方法
        return;
    }
}