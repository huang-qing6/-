#include <stdio.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

int main(){
    pid_t pid;
    int fd1[2];
    int fd2[2];

    if(pipe(fd1) == -1)
        perror("pipe");
    if(pipe(fd2) == -1)
        perror("pipe");

    pid = fork();

    if(pid == 0){
        char tmp[100];
        close(fd1[1]);
        close(fd2[0]);
        int i;

        while(1){
            memset(tmp, '/0', sizeof(tmp));
            read(fd1[0], tmp, sizeof(tmp));

            for(i = 0; i < sizeof(tmp); i++)
                tmp[i] = toupper(tmp[i]);

            write(fd2[1], tmp, sizeof(tmp));
        } 
    }else if(pid > 0){
        char tmp[100];
        close(fd1[0]);
        close(fd2[1]);
        
        printf("need to type keyboard\n");
        while(1){
            memset(tmp, '/0', sizeof(tmp));
            gets(tmp);
            write(fd1[1], tmp, sizeof(tmp));

            memset(tmp, '/0', sizeof(tmp));
            read(fd2[0], tmp, sizeof(tmp));
            printf("after trans: %s\n", tmp);
        }
    }

    return 0;
}