/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年11月20日 星期四 09时16分44秒
 ************************************************************************/
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <list>
#include <atomic>
#include <vector>
#include <algorithm>
#include <memory>
#include <condition_variable>


#include "threadpool.h"

//#include <vld.h>

using namespace std;
class A
{
public:
    A()
    {}
    ~A(){}
public:
    void foo(int k)
    {
        //sleep for a while
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 900 + 100));
        std::cout << "k = " << k << std::endl;

    }
};

//a function which will be executed in sub thread.
void hello()
{
    //sleep for a while
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << "hello  \n";
}

//let's test the thread.
int main()
{
    srand(0);

    ThreadPool g_threadPool(3,20);
    A a;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, a, 1))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 2))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 3))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 4))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 5))<<endl;
    
    g_threadPool.start();
    
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, a, 1))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 2))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 3))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 4))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 5))<<endl;

    
    
    char temp;
    cin >> temp;
    if (temp == 'e')
    {
        g_threadPool.stop();
    }
   
    g_threadPool.start();
    
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, a, 1))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 2))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 3))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 4))<<endl;
    cout<<(bool)g_threadPool.append_task(std::bind(&A::foo, &a, 5))<<endl;

    //g_threadPool.~ThreadPool();
    this_thread::sleep_for(chrono::seconds(3));

    //cout<<"threadpool deconstruct"<<endl;
    return 0;
}

