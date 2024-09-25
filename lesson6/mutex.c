#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <pthread.h>

void *thread_func1(void *arg);
void *thread_func2(void *arg);

pthread_mutex_t mutex;

int main(){
    pthread_t pthread1, pthread2;
    int ret;
    pthread_mutex_init(&mutex, NULL);

    ret = pthread_create(&pthread1, NULL, thread_func1, NULL);
    if(ret != 0){
        perror("pthread1_create");
        exit(0);
    }
    ret = pthread_create(&pthread2, NULL, thread_func2, NULL);
    if(ret != 0){
        perror("pthread2_create");
        exit(0);
    }

    while(1){
        sleep(1);
    }

    printf("thread is term\n");
    return 0;
}

void *thread_func1(void *arg){
    int i;
    while(1){
        pthread_mutex_lock(&mutex);
        for(i = 0; i < 10; i++){
            printf("hello world\n");
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void *thread_func2(void *arg){
    sleep(1);
    printf("pthread2 is running\n");
    int i;
    while(1){
        pthread_mutex_lock(&mutex);
        for(i = 0; i < 10; i++){
            printf("Good morning\n");
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}