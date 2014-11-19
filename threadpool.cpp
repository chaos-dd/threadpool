/*************************************************************************
	> File Name: threadpool.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年11月19日 星期三 17时42分56秒
 ************************************************************************/

#include "threadpool.h"
#include "thread.h"

ThreadPool::ThreadPool():poolSize(10),maxQueueSize(20),
   queSem(0), curQueueSize(0)
{
    taskQueue=std::list<task>();
    threads=std::vector<std::shared_ptr<Thread> >(10);
}
void ThreadPool::start()
{  
    for(auto ptr: threads)
       ptr->start();
}

void ThreadPool::stop()
{
    bstop=true;
    taskQueue.clear();
    queSem.signal();
}

void ThreadPool::append_task(task t)
{
    std::lock_guard<std::mutex> lg(mu_tq);
    if(curQueueSize<maxQueueSize)
    {
        curQueueSize++;
        taskQueue.push_back(t);
        queSem.signal();
    }
}


