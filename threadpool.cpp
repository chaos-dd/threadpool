/*************************************************************************
	> File Name: threadpool.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年11月19日 星期三 17时42分56秒
 ************************************************************************/

#include "threadpool.h"
#include "thread.h"

ThreadPool::ThreadPool():ThreadPool(10,20)
{
}
ThreadPool::ThreadPool(int _poolSize,int _maxQueueSize):poolSize(_poolSize),maxQueueSize(_maxQueueSize),
    threads(_poolSize)
{
    taskQueue=std::list<task>();
    for(auto &t:threads)
        t=std::thread(std::bind(&ThreadPool::run_task,this));
}
ThreadPool::~ThreadPool()
{
    for(auto &t:threads)
        t.detach();
}
void ThreadPool::start()    
{  
    std::unique_lock<std::mutex> ul_stop(mu_stop);
    if(bstop==true)    
    {
        bstop=false;
       stop_cond.notify_all();
    }
}

void ThreadPool::stop()
{
    std::unique_lock<std::mutex> ul_stop(mu_stop);
    bstop=true;
    stop_cond.notify_all();
}

bool ThreadPool::append_task(task t)
{
    std::lock_guard<std::mutex> lg(mu_tq);
    if(taskQueue.size()<maxQueueSize)
    {
        taskQueue.push_back(t);
        task_cond.notify_one();
        return true;
    }

    return false;
}

void ThreadPool::run_task()
{
    while(true)
    {
        std::unique_lock<std::mutex> ul_tq(mu_tq);
        task_cond.wait(ul_tq,[this](){
            return !taskQueue.empty();
            });  
        ul_tq.unlock();

        std::unique_lock<std::mutex> ul_stop(mu_stop);
        while(bstop)
            stop_cond.wait(ul_stop);
        ul_stop.unlock();
        
        if(!ul_tq.try_lock())
            continue;  
        task t=taskQueue.front();
        taskQueue.pop_front();
        ul_tq.unlock();
        t();
    }
}
