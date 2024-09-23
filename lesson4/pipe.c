#include <stdio.h>
#include <sys/types.h>
#include <sys/unistd.h>


// 父进程负责写入，子进程读出
int main(){
    int fd[2];
    if( pipe(fd) == -1)
        perror("pipe");

    pid_t pid = fork();
    if(pid > 0){
        close(fd[0]);
        sleep(5);
        write(fd[1], "ad", 2);
    } else if(pid == 0){
        char ch[2];

        printf("Child process is waiting for data: \n");
        close(fd[1]);
        sleep(5);
        read(fd[0], &ch, 2);
        printf("read from pipe: %s\n", ch);
    }

    return 0;
}