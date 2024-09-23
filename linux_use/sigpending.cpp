// sigpending 用于获取当前进程的未决信号集（屏蔽未处理信号）

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig){
    printf("Caught signal %d\n", sig);
}

int main(){
    sigset_t set, pending;
    
    // 设置信号处理程序
    signal(SIGUSR1, handler);

    // 初始化信号集并添加SIGUSR1信号
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    // 屏蔽SIGUSR1信号给当前进程
    raise(SIGUSR1);
    printf("SIGUSR1 sent but should be blocked\n");

    // 检查未决信号
    sigpending(&pending);

    if(sigismember(&pending, SIGUSR1)){
        printf("SIGUSR1 is pending\n");
    } else {
        printf("SIGUSR1 is not pending\n");
    }

    // 接触信号屏蔽
    sigprocmask(SIG_UNBLOCK, &set, NULL);

    return 0;
}