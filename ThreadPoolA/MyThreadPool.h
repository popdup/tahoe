#ifndef MYTHREADPOOL_H_
#define MYTHREADPOOL_H_

#include "MyWorkThread.h"
#include "BaseJob.h"
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <cassert>
#include <algorithm>
using namespace std;

class MyThreadPool {
 friend class MyWorkThread;

private:
 class MyThreadMutex{
 private:
  pthread_mutex_t _lock;
 public:
  MyThreadMutex(){pthread_mutex_init(&_lock,NULL);}
  ~MyThreadMutex(){pthread_mutex_destroy(&_lock);}
  void Lock(){pthread_mutex_lock(&_lock);}
  void Unlock(){pthread_mutex_unlock(&_lock);}
 };

public:
	 MyThreadPool();
	 MyThreadPool(int initNum);
	 virtual ~MyThreadPool();

	 MyThreadMutex m_BusyMutex;
	 MyThreadMutex m_IdleMutex;

    vector<MyWorkThread*>  m_BusyList; //Thread List
    vector<MyWorkThread*>  m_IdleList; //Idle List

    void    SetMaxNum(int maxnum){m_MaxNum = maxnum;}
    int    GetMaxNum(void){return m_MaxNum;}

    int    GetBusyNum(void){return m_BusyList.size();}
    int  GetIdleNum(void){return m_IdleList.size();}

    int  GetAllNum(void){return m_BusyList.size()+m_IdleList.size();}

    void    SetInitNum(int initnum){m_InitNum = initnum;}
    int    GetInitNum(void){return m_InitNum;}

    void    TerminateAll(void);
    void    Run(BaseJob* job, void* jobdata);

protected:
	MyWorkThread* GetIdleThread(void);
    void AppendToIdleList(MyWorkThread* jobthread);//加到空闲现场池
    void MoveToBusyList(MyWorkThread* idlethread);//加到忙碌线程池
    void MoveToIdleList(MyWorkThread* busythread);//移到空闲线程池
    void CreateIdleThread(int num); //创建空闲线程池

private:
 unsigned int m_InitNum;
 unsigned int m_MaxNum;  //the max value of the thread
};

#endif /* MYTHREADPOOL_H_ */