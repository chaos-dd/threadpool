/*************************************************************************
	> File Name: thread.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年11月19日 星期三 17时43分01秒
 ************************************************************************/


#include "thread.h"
#include <mutex>
#include "threadpool.h"



Thread::Thread(ThreadPool *pool)
{
    pThreadPool.reset(pool);
}
void Thread::start()
{
    pThread.reset(new std::thread(std::bind(&Thread::run,this)));
}
void Thread::run()
{
    while(true)
    {
        pThreadPool->queSem.wait();
        std::unique_lock<std::mutex> lg(pThreadPool->mu_tq);
           
        if(pThreadPool->taskQueue.size()==0)
            return;
        task t=pThreadPool->taskQueue.front();
        pThreadPool->taskQueue.pop_front();
        lg.unlock();
        t();
        //pThreadPool->poolSem.signal();
    }
}
