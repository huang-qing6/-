#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


#define BUFFER_SIZE 1024

int main(){
    int fd;
    ssize_t bytes_written, bytes_read;
    off_t offset;
    char buffer[BUFFER_SIZE];

    // 打开文件， flag正确设置不然就寄
    if((fd = open("example.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 写入数据到文件
    const char *data_to_write = "Hello World!";
    if((bytes_written = write(fd, data_to_write, strlen(data_to_write))) == -1){
        perror("write");
        exit(EXIT_FAILURE);
    }
    printf("Bytes written: %ld\n", bytes_written);

    // 设置文件偏移量
    if((offset = lseek(fd, 0, SEEK_SET)) == -1){
        perror("lseek");
        exit(EXIT_FAILURE);        
    }

    // 读取文件数据
    if((bytes_read = read(fd, buffer, BUFFER_SIZE)) == -1){
        perror("read");
        exit(EXIT_FAILURE);          
    }
    printf("Bytes read: %ld\n", bytes_read);
    printf("Data read: %.*s\n", (int)bytes_read, buffer);

    if(close(fd) == -1){
        perror("close");
        exit(EXIT_FAILURE);             
    }

    return 0;
}