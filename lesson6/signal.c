#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

void func(int);

int main(){
    signal(SIGINT, func);
    signal(SIGKILL, func);

    printf("cur pid: %d\n", getpid());
    int i = 0;
    while(1){
        printf("Count to %d\n", i++);
        sleep(1);
    }

    return 0;
}

void func(int signal){
    if(signal == SIGINT){
        printf("you have just triggered a ctrl+c operation.\n");
        exit(1);
    } else if(signal == SIGKILL) { // 不可以重新定义，所以没有执行下面语句
        printf("Trig a SIGKILL signal.\n");
    }
}
