#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int ret;
    char buf[100];

    if(argc == 1){
        printf("too few args");
        return 0;
    }
        

    int fd;
    if((fd = open("my_fifo", O_WRONLY)) == -1)
        perror("open");

    strcpy(buf, argv[1]);
    write(fd, buf, sizeof(buf));
    printf("Write to named pipe: %s\n", buf);

    return 0;
}