/*************************************************************************
	> File Name: thread.h
	> Author: 
	> Mail: 
	> Created Time: 2014年11月19日 星期三 17时42分59秒
 ************************************************************************/

#ifndef _THREAD_H
#define _THREAD_H

#include<thread>
#include<memory>
#include<functional>

class ThreadPool;
class Thread
{
    friend class ThreadPool;
    typedef std::function<void(void)> task;
    public:
        Thread(ThreadPool * pool);
        void start();
        void run();
    private:    
        std::shared_ptr<std::thread> pThread;
        std::shared_ptr<ThreadPool> pThreadPool;
};
#endif
