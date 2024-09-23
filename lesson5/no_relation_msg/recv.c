#include <stdio.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MY_TYPE 9527
#define MY_KEY 1314

int main(){
    pid_t pid;
    int msgid;

    struct msgbuff // 发送结构体
    {
        long mtype;
        char mtext[100]; // 发送
        int number; // 发送
    };
    
    struct msgbuff buf;
    msgid = msgget(MY_KEY, IPC_CREAT);

    while(1){
        printf("process is waiting:\n");
        msgrcv(msgid, &buf, sizeof(buf) - sizeof(buf.mtype), MY_TYPE, 0);
        printf("process read from msg:%s, %d\n", buf.mtext, buf.number);  
    }
    msgctl(msgid, IPC_RMID, NULL);  
    return 0;
}