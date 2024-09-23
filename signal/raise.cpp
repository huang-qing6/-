#include <stdio.h>
#include <signal.h>

int main(){
    int result = raise(SIGINT);

    // SIGINT 终止
    if(result == 0){
        printf("signal sent successfully\n");
    }else{
        printf("fail to send signal\n");
    }
    return 0;
}