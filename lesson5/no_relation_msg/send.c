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
    int msgid; // 修改键值保证一样

    struct msgbuff // 发送结构体
    {
        long mtype;
        char mtext[100]; // 发送
        int number; // 发送
    };
    
    struct msgbuff buf;
    msgid = msgget(MY_KEY, IPC_CREAT);

    sleep(5);
    
    buf.mtype = MY_TYPE;
    printf("please user type a string\n");
    gets(buf.mtext);
    printf("please user type a number\n");
    scanf("%d", buf.number);

    msgsnd(msgid, &buf,  sizeof(buf) - sizeof(buf.mtype), 0);

    return 0;
}