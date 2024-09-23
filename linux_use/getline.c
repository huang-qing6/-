#include <stdio.h>

int main(){
    // 创建临时文件
    FILE *tmpFile = tmpfile();

    if(tmpFile != NULL){
        // 向临时文件写入数据
        fprintf(tmpFile, "This is a temporay file.\n");
        fprintf(tmpFile, "it is created using tmpfile() function.\n");

        // 将指针移到文件开头
        rewind(tmpFile);

        // 从临时文件指针移到文件开头
        char buffer[100];
        while(fgets(buffer, sizeof(buffer), tmpFile) != NULL){
            printf("%s", buffer);
        }

        // 关闭临时文件
        fclose(tmpFile);
    } else {
        printf("Failed to create temporary file.\n");
    }

    return 0;
}