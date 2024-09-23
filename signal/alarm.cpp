#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig){
    printf("Alarm triggered\n");
}

int main(){
    signal(SIGALRM, handler);
    unsigned int remaining = alarm(5);
    printf("Waiting for alarm...\n");
    sleep(10);
    printf("Resuming after alarm\n");
    return 0;
}