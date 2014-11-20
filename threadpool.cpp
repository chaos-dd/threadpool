/*************************************************************************
	> File Name: threadpool.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年11月19日 星期三 17时42分56秒
 ************************************************************************/

#include "threadpool.h"
#include <iostream>
ThreadPool::ThreadPool():ThreadPool(10,20)
{
}
ThreadPool::ThreadPool(size_t _poolSize,size_t _maxQueueSize):poolSize(_poolSize),maxQueueSize(_maxQueueSize),
   exit(false),bstop(true),threads(_poolSize)
{
    taskQueue=std::list<task>();
    for(auto &t:threads)
        t=std::thread(std::bind(&ThreadPool::run_task,this));
}
ThreadPool::~ThreadPool()
{
    exit=true;
    cond.notify_all();
    for(auto &t:threads)
        t.join();
}
void ThreadPool::start()    
{  
    if(bstop==true)    
    {
       bstop=false;
       cond.notify_all();
    }
}

void ThreadPool::stop()
{
    if(bstop==false)
    {
        bstop=true;
    }
}

bool ThreadPool::append_task(task t)
{
    std::lock_guard<std::mutex> lg(mu);
    if(taskQueue.size()<maxQueueSize)
    {
        taskQueue.push_back(t);
        cond.notify_one();
        return true;
    }
    return false;
}

void ThreadPool::run_task()
{
    while(true)
    {
        std::unique_lock<std::mutex> ul(mu);
        while( bstop || taskQueue.empty())
        {
            cond.wait(ul);
            if(exit==true)
                return ; 
        }
        task t=taskQueue.front();
        taskQueue.pop_front();
        ul.unlock();
        t();
    }
}
