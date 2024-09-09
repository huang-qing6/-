#include <pthread.h>

typedef struct Task
{
    void(*function)(void* arg);
    void* arg;
} Task;

// 线程池结构体
typedef struct ThreadPool{
    //任务队列
    Task* taskQ;
    int queueCapacity;
    int queueSize;
    int queueFront;
    int queueRear;

    pthread_t managerID;
    pthread_t *threadIDs;
    int minNum;
    int maxNum;
    int busyNum;
    int liveNum;
    int exitNum; // 将销毁线程个数
    pthread_mutex_t mutexPool;
    pthread_mutex_t mutexBusy;
    pthread_cond_t notFull;
    pthread_cond_t notEmpty;

    int shutdown;
}ThreadPool;

/***    Fuc     ***/
// 创建线程池
ThreadPool *threadPoolCreate(int min, int max, int queueSize);

// 销毁线程池
int threadPoolDestroy(ThreadPool* poll);

// 分配任务
void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg);

// 获取线程池中工作线程个数
int threadPoolBusyNum(ThreadPool* pool);

// 获取线程池中线程存活个数
int threadPoolAliveNum(ThreadPool* pool);

// 线程退出
void threadExit(ThreadPool* pool);

// 消费者
void* worker(void* arg);

// 管理者
void* manager(void* arg);