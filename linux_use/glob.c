#include <glob.h> // 特定模式匹配
#include <stdio.h>
#include <stdlib.h>

int main(){
    glob_t globbuf;
    int ret;

    // 匹配当前目录下的所有.txt文件:
    ret = glob("*.txt", 0, NULL, &globbuf);
    if(ret == 0){
        for(size_t i = 0; i < globbuf.gl_pathc; i++){
            printf("%s\n", globbuf.gl_pathv[i]);
        }
        globfree(&globbuf); // 释放分配的内存
    } else {
        printf("No matchs found or an error occurred\n");
    }

    return 0;
}

