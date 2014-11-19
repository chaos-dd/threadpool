/*************************************************************************
	> File Name: threadpool.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年11月19日 星期三 17时42分56秒
 ************************************************************************/

#include "threadpool.h"


void ThreadPool::start()
{
    serv_thread.reset(new std::thread(std::bind(start_in_thread,this)))
}

void ThreadPool::stop()
{
    serv_thread.get()->join();
}

void ThreadPool::append_task(task t)
{
    std::lock_guard<std::mutex> > lg(m_tq);
    taskQueue.push_back(t);
}

void ThreadPool::start_in_thread()
{
   for(auto ptr: threads)
       ptr->run();
    
   while(stop)
   {
       :
   }
};
