#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handle(int signum){
    printf("Received signal %d\n", signum);
}

int main(){
    // 安装信号处理程序
    signal(SIGINT, signal_handle);

    sigset_t new_mask, old_mask;

    // 初始化空信号集
    sigemptyset(&new_mask);

    // 将SIGINT信号添加到新的信号集中
    sigaddset(&new_mask, SIGINT);

    // 设置新的信号屏蔽字
    if(sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0){
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("SIGINT is blocked, press Crtl+c to send SIGINT\n");
    sleep(5); //等待五秒，此时SIGINT被阻塞

    // 解除对SIGINT信号的屏蔽
    if(sigprocmask(SIG_UNBLOCK, &new_mask, NULL) < 0){
        perror("sigprocmask");
        exit(EXIT_FAILURE);        
    }

    printf("SIGINT is unblocked, now you can send SIGINT\n");

    while(1)
        sleep(1);

    return 0;
}

// 心得：类似中断屏蔽，不过所有按位操作的行为都可以这么理解