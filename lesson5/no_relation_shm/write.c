#include <stdio.h>
// shm需要调用的头文件
#include <sys/ipc.h>
#include <sys/shm.h>
//
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

char msg[] = "hello world";

// shmctl() 对共享内存段进行控制
#define MY_KEY 9527

int main(){
    int shmid = shmget(MY_KEY, 1024, IPC_CREAT); // 返回一个大小1024的共享内存
    char* addr = shmat(shmid, NULL, 0); // 绑定共享内存
    memset(addr, '/0', sizeof(msg));
    memcpy(addr, msg, sizeof(msg));

    shmdt(addr); // 解除绑定共享内存

    shmctl(shmid, IPC_RMID, NULL); // 删掉了共享内存了
    return 0;
}