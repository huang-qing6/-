#include <stdio.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    int fd[2];

    if(pipe(fd) == -1)
        perror("pipe");

    pid = fork();

    if(pid == 0){
        char ch = '*';
        int n = 0;

        close(fd[0]);
        while(1){
            write(fd[1], &ch, 1);
            printf("count = %d\n", n++);
        } 
    }else if(pid > 0){
         waitpid(pid, NULL, 0);
    }

    return 0;
}