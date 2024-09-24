#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    sem_t *sem;
    int i = 0;
    sem = sem_open("NAME_SEM", O_CREAT, 0666, 0);

    while(1){
        sem_wait(sem);
        printf("Process 1, i = :%d\n", i++);
    }

    sem_close(sem); // 关闭信号量
    // sem_unlink 取消信号量

    return 0;
}