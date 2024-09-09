#include "thread_pool.h"
#include <memory.h>
#include <stdio.h>
#include <unistd.h>

#define NUMBER 10

ThreadPool *threadPoolCreate(int min, int max, int queueSize){
    ThreadPool *pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    do{
        if(pool == NULL){
            printf("ThreadPool malloc err\n");
            break;
        }

        pool->threadIDs = (pthread_t*)malloc(sizeof(pthread_t)*max);
        
        if(pool->threadIDs == NULL){
            printf("threadIDs == NULL");
            break;
        }

        memset(pool->threadIDs, 0, sizeof(pthread_t)*max);

        pool->minNum = min;
        pool->maxNum = max;
        pool->busyNum = 0;
        pool->liveNum = min;
        pool->exitNum = 0;

        if(pthread_mutex_init(&pool->mutexPool, NULL) != 0 ||
            pthread_mutex_init(&pool->mutexBusy, NULL) != 0 ||
            pthread_cond_init(&pool->notEmpty, NULL) != 0 ||
            pthread_cond_init(&pool->notFull, NULL) != 0){
                printf("mutex or condition init fail...\n");
                break;
            }

        pool->queueCapacity = queueSize;
        pool->queueSize = 0;
        pool->queueFront = 0;
        pool->queueRear = 0;
        pool->taskQ = malloc(sizeof(Task)*queueSize);
        
        pool->shutdown = 0;

        pthread_create(&pool->managerID, NULL, manager, NULL);

        for(int i = 0; i < min; i++)
            pthread_create(&pool->threadIDs[i], NULL, worker, NULL);

        return pool;
    }while(0);

    if(pool->threadIDs)free(pool->threadIDs);
    if(pool->taskQ)free(pool->taskQ);
    if(pool)free(pool);

    return NULL;
}

// 线程池添加任务
void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg){
    pthread_mutex_lock(&pool->mutexPool);

    while(pool->queueSize == pool->queueCapacity 
        && !pool->shutdown){
        pthread_cond_wait(&pool->notFull, &pool->mutexPool);
    }

    if(pool->shutdown){
        pthread_mutex_unlock(&pool->mutexPool);
        return;
    }

    // add task
    pool->taskQ[pool->queueRear].function = func;
    pool->taskQ[pool->queueRear].arg = arg;

    pool->queueRear = (pool->queueRear+1)%pool->queueCapacity;

    pool->queueSize++;

    pthread_cond_signal(&pool->notEmpty);

    pthread_mutex_unlock(&pool->mutexPool);
}

// 获取线程池工作个数
int threadPoolBusyNum(ThreadPool* pool){
    pthread_mutex_lock(&pool->mutexBusy);
    int busyNum = pool->busyNum;
    pthread_mutex_unlock(&pool->mutexBusy);
    return busyNum;
}

// 查询存活数量
int threadPoolAliveNum(ThreadPool* pool){
    pthread_mutex_lock(&pool->mutexBusy);
    int alivenum = pool->liveNum;
    pthread_mutex_unlock(&pool->mutexBusy);
    return alivenum;    
}

// 销毁线程池
int threadPoolDestroy(ThreadPool* pool){
    if(pool == NULL)
        return -1; // err

    pool->shutdown = -1;
    // 阻塞回收管理者线程
    pthread_join(pool->managerID, NULL);
    // 唤醒阻塞的消费者线程
    for(int i = 0; i < pool->liveNum; i++)
        pthread_cond_signal(&pool->notEmpty);
    
    if(pool->taskQ)
        free(pool->taskQ);

    if(pool->threadIDs)
        free(pool->threadIDs);

    pthread_mutex_destroy(&pool->mutexPool);
    pthread_mutex_destroy(&pool->mutexBusy);
    pthread_cond_destroy(&pool->notEmpty);
    pthread_cond_destroy(&pool->notFull);

    free(pool);
    pool = NULL;

    return 0;
}

// 管理者线程任务函数
void* manager(void* arg){
    ThreadPool *pool = (ThreadPool*)arg;

    while(!pool->shutdown){
        sleep(3);

        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->queueSize;
        int liveNum = pool->liveNum;
        pthread_mutex_unlock(&pool->mutexPool);

        pthread_mutex_lock(&pool->mutexBusy);
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);        

        if(queueSize > liveNum && liveNum < pool->maxNum){
            pthread_mutex_lock(&pool->mutexPool);
            int counter = 0;
            for(int i = 0; i < pool->maxNum && counter < NUMBER 
                && pool->liveNum < pool->maxNum; ++i){
                if(pool->threadIDs[i] == 0){
                    pthread_create(&pool->threadIDs[i], NULL, worker, pool);
                    counter++;
                    pool->liveNum++;                    
                }
            }
            pthread_mutex_unlock(&pool->mutexPool);             
        }

        // 销毁线程
        if(busyNum * 2 < liveNum && liveNum > pool->minNum){
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum = NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);

            for(int i = 0; i < NUMBER; ++i){
                pthread_cond_signal(&pool->notEmpty);
            }
        }
    }

    return NULL;
}

// 添加线程任务
void* worker(void* arg){
    ThreadPool *pool = (ThreadPool*)arg;
    while(1){
        pthread_mutex_lock(&pool->mutexPool);

        while(pool->queueSize == 0 && !pool->shutdown){
            pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);
        }

        if(pool->shutdown){
            pthread_mutex_unlock(&pool->mutexPool);

            pthread_exit(NULL);
        }

        Task task;
        task.function = pool->taskQ[pool->queueFront].function;
        task.arg = pool->taskQ[pool->queueFront].arg;

        pool->queueFront = (pool->queueFront + 1)%pool->queueCapacity;
        pool->queueSize--;

        pthread_mutex_unlock(&pool->mutexPool);

        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum++;
        pthread_mutex_unlock(&pool->mutexBusy);
        task.function(task.arg);

        free(task.arg);
        task.arg = NULL;

        pthread_mutex_lock(&pool->mutexBusy);
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexBusy);        
    }

    return NULL;
}

// 线程退出
void threadExit(ThreadPool *pool){
    pthread_t tid = pthread_self();
    for(int i = 0; i < pool->maxNum; ++i){
        if(pool->threadIDs[i] == tid){
            pool->threadIDs[i] = 0;
            break;
        }
    }

    pthread_exit(NULL);
}