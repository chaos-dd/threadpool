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

class ThreadPool
{
    public:
        typedef std::function<void(void)> task;
        explicit ThreadPool();
        ThreadPool(size_t _poolSize, size_t _maxQueueSize);
        ~ThreadPool();
        void start();
        void stop();
        bool append_task(task t);

    private:
        void run_task();
    private:
        size_t poolSize;
        size_t maxQueueSize;
        
        bool exit;
        bool bstop;
        std::mutex mu;
        std::condition_variable cond;
        std::list<task> taskQueue;
        std::vector<std::thread> threads;

};



#endif

