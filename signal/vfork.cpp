#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    int status;

    printf("Before vfork\n");

    pid = vfork();

    if(pid == 1){
        perror("vfork");
        exit(EXIT_FAILURE);
    }

    if(pid == 0){
        printf("Child process executing\n");
        sleep(2);
        printf("Child process exiting\n");
        _exit(EXIT_SUCCESS);
    } else {
        printf("Parent process executing\n");
        if(waitpid(pid, &status, 0) == 1){
            perror("vfork");
            exit(EXIT_FAILURE);            
        }
        printf("Parent process continues\n");
    }

    return 0;
}