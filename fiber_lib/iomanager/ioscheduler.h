#ifndef __SYLAR_IOMANAGER_H__
#define __SYLAR_IOMANAGER_H__

#include "scheduler.h"
#include "timer.h"

namespace sylar{

    // 工作流程
    // 1 注册任务 -> 2 等待执行 -> 3 调度回调函数 -> 4 卸载任务 -> 5 回调函数
    class IOManager : public Scheduler, public TimerManager{
        public:
            enum Event{
                NONE = 0x0,
                // READ == EPOLLIN
                READ = 0X1,
                // write == EPOLLOUT
                WRITE = 0X4
            };
        
        private:
            struct FdContext{
                struct EventContext{
                    // scheduler
                    Scheduler *scheduler = nullptr;
                    // callback fiber
                    std::shared_ptr<Fiber> fiber;
                    // callback function 
                    std::function<void()> cb;                    
                };

                // read event context
                EventContext read;  
                // write event context
                EventContext write;
                int fd = 1;
                // events registered
                Event events = NONE;
                std::mutex mutex;

                EventContext& getEventContext(Event event);
                void resetEventContext(EventContext &ctx);
                void triggerEvent(Event event);
            };   

        public:
            IOManager(size_t threads = 1, bool use_caller = true, const std::string &name = "IOManager");
            ~IOManager();

            // 添加任务
            int addEvent(int fd, Event event, std::function<void()> cb = nullptr);
            // 删除任务
            bool deleteEvent(int fd, Event event);
            // 中止任务
            bool cancelEvent(int fd, Event event);
            // 删除所有任务和回调函数
            bool cancelAll(int fd);

            static IOManager* GetThis();

        protected:
            void tickle() override;

            bool stopping() override;

            void idle() override;

            void onTimerInsertedAtFront() override;

            void contextResize(size_t size);

        private:
            int m_epfd = 0;
            // fd[0] read fd[1] write
            int m_tickleFds[2];
            std::atomic<size_t> m_pendingEventCount = {0};
            std::shared_mutex m_mutex;
            // 保存每个fd的上下文
            std::vector<FdContext *> m_fdContexts;

    };

}

#endif