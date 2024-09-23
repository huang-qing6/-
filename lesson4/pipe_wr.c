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
        char tmp[100];
        close(fd[0]);
        printf("need to type keyboard\n");
        while(1){
            scanf("%s", tmp);
            write(fd[1], tmp, sizeof(tmp));
        } 
    }else if(pid > 0){
        char tmp[100];
        close(fd[1]);

        while(1){
            read(fd[0], tmp, sizeof(tmp));
            printf("read from pipe: %s\n", tmp);
        }
    }

    return 0;
}