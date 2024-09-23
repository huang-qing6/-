#include <stdio.h>
#include <signal.h>

// bu
void handler(int sig){
    printf("Signal received\n");
}

int main(){
    signal(SIGINT, handler);
    printf("Waiting for signal..\n");
    pause(); // 挂起进程，直到收到信号
    printf("Resuming after pause\n");
    return 0;
}