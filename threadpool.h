/*************************************************************************
	> File Name: threadpool.h
	> Author: 
	> Mail: 
	> Created Time: 2014年11月19日 星期三 17时36分28秒
 ************************************************************************/

#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include<thread>
#include<functional>
#include<mutex>
#include<vector>
#include<list>
#include<memory>
#include<condition_variable>
#include<atomic>
class Semaphore
{
    public:
        Semaphore(int cnt):count(cnt)
        {}
        void wait()
        {
            std::unique_lock<std::mutex> lock(mt);
            if(--count<0)
                cond.wait(lock);
        }
        void signal()
        {
            std::lock_guard<std::mutex> lock(mt);
            count++;
            cond.notify_one();
        }
    private:
        int count;
        std::mutex mt;
        std::condition_variable cond;
};
class Thread;
class ThreadPool
{
    friend class Thread;
    typedef std::function<void(void)> task;
    explicit ThreadPool();
    public:
        void start();
        void stop();
        void append_task(task t);

    private:
        void start_in_thread();
    private:
        int poolSize;
        int maxQueueSize;
        Semaphore queSem;
        int curQueueSize;

        std::atomic<bool> bstop;
        std::mutex mu_tq;
        std::list<task> taskQueue;
        std::vector<std::shared_ptr<Thread> > threads;

};



#endif

