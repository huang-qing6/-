#include <stdio.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MY_TYPE 9527

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

    msgid = msgget(IPC_PRIVATE, IPC_CREAT);

    pid = fork();
    if(pid > 0){
        sleep(5);

        buf.mtype = MY_TYPE;
        printf("please user type a string\n");
        gets(buf.mtext);
        printf("please user type a number\n");
        scanf("%d", buf.number);

        msgsnd(msgid, &buf,  sizeof(buf) - sizeof(buf.mtype), IPC_CREAT | 0666);
        waitpid(pid, NULL, 0);
    }else if(pid == 0){
        printf("Child process is waiting:\n");
        msgrcv(msgid, &buf, sizeof(buf) - sizeof(buf.mtype), MY_TYPE, 0);
        printf("Child process read from msg:%s, %d\n", buf.mtext, buf.number);
        msgctl(msgid, IPC_RMID, NULL);
    } else {
        perror("fork");
    }

    return 0;
}