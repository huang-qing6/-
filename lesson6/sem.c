#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>


int main(){
    sem_t *sem_id = NULL; // 存放信号量
    pid_t pid;

    // ？匿名MAP_ANONYMOUS现实错误，但是实际编译正确
    sem_id = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    sem_init(sem_id, 1, 0); //1: 信号量 2: 进程/线程通信 3: 设置信号量大小

    pid = fork();

    // 这里 sem_id 非共享信号量, 用mmap来进行共享
    if(pid > 0){
        while (1) // 父进程消耗信号量
        {
            sem_wait(sem_id); // 判断信号量是不是大于零，是则继续运行
            printf("this is p_process\n");
            sleep(1);
        }     
    } else if(pid == 0){
        while(1){
            printf("this is c_process\n");
            sleep(2);
            sem_post(sem_id); // 发布一次信号量
        }
    }


    return 0;
}