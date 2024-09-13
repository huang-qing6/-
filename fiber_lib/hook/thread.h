#ifndef _THREAD_H_
#define _THREAD_H_

#include <mutex>
#include <condition_variable>
#include <functional>

namespace sylar{

    // 用于线程间同步
    class Semaphore{
        private:
            std::mutex mtx;
            std::condition_variable cv;
            int count;

        public:
            // 初始化信号量
            explicit Semaphore(int count_ = 0) : count(count_){}

            // P操作
            void wait(){
                std::unique_lock<std::mutex> lock(mtx);
                while(count == 0){
                    cv.wait(lock);
                }
                count--;
            }

            // V操作
            void signal(){
                std::unique_lock<std::mutex> lock(mtx);
                count++;
                cv.notify_one(); // signal
            }
    };

    // 两种线程，由系统自动创建的主线程；用用户申请
    class Thread{
        public:
            Thread(std::function<void()> cb, const std::string& name);
            ~Thread();

            pid_t getId() const {return m_id;}
            const std::string& getName() const {return m_name;}

            void join();

            // 获取分配线程id
            static pid_t GetThreadId();
            // 获取当前线程id
            static Thread* GetThis();
            // 设置当前线程名字
            static const std::string& GetName();
            // 设置当前线程名字
            static void SetName(const std::string& name);

        private:
            // 线程函数
            static void* run(void* arg);

            pid_t m_id = -1;
            pthread_t m_thread = 0;

            // 线程运行需要的函数
            std::function<void()> m_cb;
            std::string m_name;

            Semaphore m_semaphore;
    };
}

#endif