// sigsuspend 会暂时替代当前信号屏蔽字，并挂起调用进程知道信号到达被捕获

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig){
    printf("Caught signal %d\n", sig);
}

int main(){
    sigset_t set, oldset, suspendset;
    
    // 设置信号处理程序
    signal(SIGUSR1, handler);

    // 初始化信号集并添加SIGUSR1信号
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    // 屏蔽USR1信号
    sigprocmask(SIG_BLOCK, &set, &oldset);
    printf("SIGUSR1 now is blocked\n");

    // 屏蔽SIGUSR1信号给当前进程
    raise(SIGUSR1);
    printf("SIGUSR1 sent but should be blocked\n");

    // 检查未决信号
    sigemptyset(&suspendset);

    // 使用suspendset挂起进程，等待信号
    sigsuspend(&suspendset);

    // 解除阻塞后，信号将被处理
    printf("SIGUSR1 is now unblocked and handled\n");

    // 接触信号屏蔽
    sigprocmask(SIG_UNBLOCK, &oldset, NULL);

    return 0;
}