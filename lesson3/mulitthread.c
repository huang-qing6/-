/*  第二个参数属于赋予线程结构体属性，暂时没用到
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*func)(void *), void *arg)
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread1_func(void *arg);
void *thread2_func(void *arg);

int count = 0;

int main(){
    pthread_t pthread1, pthread2;
    int ret;
    //int count = 5;
    ret = pthread_create(&pthread1, NULL, thread1_func, NULL);
    if(ret != 0){
        perror("pthread1_create");
        exit(0);
    }

    ret = pthread_create(&pthread2, NULL, thread2_func, NULL);
    if(ret != 0){
        perror("pthread2_create");
        exit(0);
    }

    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);
    printf("thread is term\n");

    return 0;
}

void *thread1_func(void *arg){
    int i;
    printf("Thread1 begin running\n");
    for(i = 0; i < 10; i++)
    {
        printf("count:%d hello world\n", count++);
        sleep(1);
    }
    
    return NULL;
}

void *thread2_func(void *arg){
    int i;
    printf("Thread2 begin running\n");
    for(i = 0; i < 10; i++)
    {
        printf("count:%d good morning\n", count++);
        sleep(1);
    }
    
    return NULL;
}