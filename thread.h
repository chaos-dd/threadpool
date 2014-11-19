/*************************************************************************
	> File Name: thread.h
	> Author: 
	> Mail: 
	> Created Time: 2014年11月19日 星期三 17时42分59秒
 ************************************************************************/

#ifndef _THREAD_H
#define _THREAD_H

#include<thread>
#include<memory.h>
#include<functional.h>


class Thread
{
    typedef std::function<void(void)>;
    public:
        std::thread::id get_id();
        void join();
        bool joinable();    
    private:    
        std::shared_ptr<std::thread> pThread;
};
#endif
