#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    pid_t pid;
    // 父进程返回子进程号， 子进程返回0
    pid = fork();

    int count = 0;

    if(pid < 0){
        return 0;
    } else if(pid == 0) {
        for(int i = 0; i < 10; i++){
            printf("child:%d, count: %d\n", pid,  count++);
            sleep(1);
        }
    } else {
        while(1){
            printf("parent:%d, pid: %d\n", pid,  count++);
            sleep(1);
        }
    }
    

    return 0;
}