/*  第二个参数属于赋予线程结构体属性，暂时没用到
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*func)(void *), void *arg)
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_func(void *arg);

int main(){
    pthread_t pthread;
    int ret;
    int count = 5;

    ret = pthread_create(&pthread, NULL, thread_func, &count);
    if(ret != 0){
        perror("pthread_create");
        exit(0);
    }
    // 没有确保进程存活线程不一定能执行完
    //while(1);
    // 用于等待指定线程执行
    pthread_join(pthread, NULL);
    printf("thread is term\n");

    return 0;
}

void *thread_func(void *arg){
    int i;
    printf("Thread begin running\n");
    for(i = 0; i < *(int*)arg; i++)
    {
        printf("hello world\n");
        sleep(1);
    }
    
    return NULL;
}