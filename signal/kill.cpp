#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(){
    pid_t pid = getpid();
    int result = kill(pid, SIGKILL);

    // 输出已杀死，不会到下面了
    if(result == 0){
        printf("signal sent successfully\n");
    }else{
        printf("fail to send signal\n");
    }
    return 0;
}