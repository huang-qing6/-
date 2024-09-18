#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    pid_t child_pid;
    int numDead;
    int i;

    for(i = 1; i < argc; i++){
        switch (fork())
        {
        case -1:
            perror("fork()");
            exit(0);
        case 0:
            printf("child: %d pid: %d, sleeping %s seconds\n", i, getpid(), argv[i]);
            sleep(atoi(argv[i]));
            exit(0);
        default:
            break;
        }
    }
    numDead = 0;

    while(1){
        child_pid = wait(NULL);

        if(child_pid == -1){
            printf("no more child!\n");
            exit(0);
        }

        numDead++;
        printf("finish: %d, deadnum: %d\n", child_pid, numDead);
    }

    return 0;
}