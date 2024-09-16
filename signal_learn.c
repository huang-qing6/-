#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// 自定义信号处理函数
void sigint_handle(int signum){
    printf("收到sigint信号，准备退出...\n");
    // TODO 清理操作
    exit(0);
}

int main(){
    // 注册sigint信号处理函数
    // 重点在于signal函数的使用
    if(signal(SIGINT, sigint_handle) == SIG_ERR){
        perror("无法注册sigint信号处理函数");
        return 1;
    }

    // Ctrl + c 会发送SIGINT
    printf("使用Ctrl + c \n");

    // loop
    while(1)
        sleep(1);

    return 0;
}