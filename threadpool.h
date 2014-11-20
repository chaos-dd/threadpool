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
    public:
        explicit ThreadPool();
        ThreadPool(int _poolSize, int _maxQueueSize);
        ~ThreadPool();
        void start();
        void stop();
        bool append_task(task t);

    private:
        void run_task();
    private:
        int poolSize;
        int maxQueueSize;
       
        std::mutex mu_stop;
        std::condition_variable stop_cond;
        bool bstop;
        std::mutex mu_tq;
        std::condition_variable task_cond;
        std::list<task> taskQueue;
        std::vector<std::thread> threads;

};



#endif

