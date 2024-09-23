/**
 * #include <utime.h>
 * int utime(const char *filename, const struct utimnbuf *times);
 * 用于修改指向文件时间戳,times 里面包括actime 和 modtime
 */

#include <stdio.h>
#include <utime.h>
#include <time.h>
#include <sys/stat.h>

int main(){
    const char *filename = "example.txt";

    struct stat flieStat;
    if(stat(filename, &flieStat) == 0){
        printf("原始访问时间： %s\n", ctime(&flieStat.st_atime));
        printf("原始修改时间： %s\n", ctime(&flieStat.st_mtime));
    }
    
    // 设置新时间
    struct utimbuf new_times;
    new_times.actime = time(NULL) - 3600;
    new_times.modtime = time(NULL) - 7200;

    if(utime(filename, &new_times) == 0){ // 修改文件时间
        printf("文件时间更新成功。\n");
    }else{
        printf("文件时间更新失败。\n");
    }

    // 打印新的时间戳
    if(stat(filename, &flieStat) == 0){
        printf("新访问时间： %s\n", ctime(&flieStat.st_atime));
        printf("新修改时间： %s\n", ctime(&flieStat.st_mtime));        
    }

    return 0;
}