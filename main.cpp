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

    ThreadPool g_threadPool(3,4);
    g_threadPool.start();
    A a;
    g_threadPool.append_task(&hello);


    //append object method with copy-constructor(value-assignment)    
    g_threadPool.append_task(std::bind(&A::foo, a, 1));
    g_threadPool.append_task(std::bind(&A::foo, a, 2));
    g_threadPool.append_task(std::bind(&A::foo, a, 3));
    g_threadPool.append_task(std::bind(&A::foo, a, 4));
    
    //auto beg = std::chrono::high_resolution_clock().now();    


    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));   

    g_threadPool.append_task(&hello);
    //append_task object method with address assignment, will cause the objects' member increase.
    g_threadPool.append_task(std::bind(&A::foo, &a, 5));
    g_threadPool.append_task(std::bind(&A::foo, &a, 6));
    g_threadPool.append_task(std::bind(&A::foo, &a, 7));
    g_threadPool.append_task(std::bind(&A::foo, &a, 8));
    
    //std::this_thread::sleep_for(std::chrono::seconds(5));
    char temp;
    cin >> temp;
    if (temp == 'e')
    {
        g_threadPool.stop();
    }
    
    //auto end = std::chrono::high_resolution_clock().now();
    //auto dd = std::chrono::duration_cast<chrono::seconds>(end - beg);
    //cout << dd.count() << endl;

    return 0;
}
