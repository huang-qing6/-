#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <pthread.h>

void *thread_func1(void *arg);
void *thread_func2(void *arg);

int count = 0;
sem_t sem;

int main(){
    pthread_t pthread1, pthread2;
    int ret;
    sem_init(&sem, 0, 0);

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
    while(1){
        sem_wait(&sem);
        printf("pthread1 count:%d\n", count++);
        sleep(1);
    }
    
    return NULL;
}

void *thread_func2(void *arg){
    while(1){
        printf("pthread2 running:\n");
        sleep(1);
        sem_post(&sem);
    }
    
    return NULL;
}