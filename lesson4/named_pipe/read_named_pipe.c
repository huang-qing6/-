#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
    int ret, fd; 
    char buf[100];

    ret = mkfifo("my_fifo", 666);
    if (ret != 0)// 666代表有权限有读写
        perror("mkfifo");

    printf("Prepare reading from named pipe:\n");

    if((fd = open("my_fifo", O_RDWR)) == -1){
        perror("open");
        return 0;
    }
        

    while(1){
        memset(buf, '\0', sizeof(buf)); // 养成清空好习惯
        read(fd, buf, sizeof(buf));
        printf("Read from named pipe: %s\n", buf);
        sleep(1);
    }

    return 0;
}