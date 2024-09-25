// 用于杀死signal进程

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    kill(atoi(argv[1]), SIGKILL);
    return 0;
}