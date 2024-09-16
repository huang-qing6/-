#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    pid_t pid1,pid2;
    // 父进程返回子进程号， 子进程返回0
    pid1 = fork();
    pid2 = fork();

    printf("getpid:%d, pid1: %d, pid2: %d\n", getpid(),  pid1, pid2);

    return 0;
}