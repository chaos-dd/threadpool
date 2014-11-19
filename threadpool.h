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
#include<memory>

class Thread;
class ThreadPool
{
    typedef std::function<void(void)> task;
    public:
        void start();
        void stop();
        void append_task(task t);

    private:
        void start_in_thread();
    private:
        int poolSize;
        int queueSize;

        std::mutex mu_tq;
        std::list<task> taskQueue;
        std::vector<std::shared_ptr<Thread*> > threads;

        std::shared_ptr<std::Thread> serv_thread;
};



#endif

