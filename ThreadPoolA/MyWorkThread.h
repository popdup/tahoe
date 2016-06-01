#ifndef MYWORKTHREAD_H_
#define MYWORKTHREAD_H_

#include "MyThread.h"
#include "BaseJob.h"
#include "unistd.h"
//#include "MyThreadPool.h"

class MyThreadPool;

class MyWorkThread:public MyThread{

private:
 BaseJob*  m_pJob;
 void*  m_pJobdata;
 MyThreadPool* m_pThreadPool;
public:
 MyWorkThread();
 virtual ~MyWorkThread();

 void Run();
 void SetJob(BaseJob* job, void* jobdata);
 BaseJob* GetJob(void){return m_pJob;}

 void SetThreadPool(MyThreadPool* threadpool);
 MyThreadPool* GetThreadPool(void){return m_pThreadPool;}
};

#endif /* MYWORKTHREAD_H_ */