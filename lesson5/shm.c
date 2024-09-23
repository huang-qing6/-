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

int main(){
    int shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0664); // 返回一个大小1024的共享内存
    pid_t pid;


    pid = fork();
    if(pid > 0){
        char* p_addr = shmat(shmid, NULL, 0); // 绑定共享内存

        memset(p_addr, '/0', sizeof(msg));
        memcpy(p_addr, msg, sizeof(msg));

        shmdt(p_addr); // 解除绑定共享内存

        waitpid(pid, NULL, 0);
    }else if(pid == 0){
        char* c_addr = shmat(shmid, NULL, 0);
        printf("Child process waiting\n");
        sleep(3);
        printf("Child read from shared memory: %s\n", c_addr);
        shmdt(c_addr);
    } else {
        perror("fork");
    }

    return 0;
}