#include <stdio.h>
// shm需要调用的头文件
#include <sys/ipc.h>
#include <sys/shm.h>
//
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MY_KEY 9527

int main(){
    int shmid = shmget(MY_KEY, 1024, IPC_CREAT); // 返回一个大小1024的共享内存
    char* addr = shmat(shmid, NULL, 0); // 绑定共享内存


    printf("read from shared memory: %s\n", addr);
    shmdt(addr); // 解除绑定共享内存
    return 0;
}