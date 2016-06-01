#ifndef MYTHREAD_H_
#define MYTHREAD_H_

#include <cassert>
#include "pthread.h"

class MyThread {

public:
 MyThread();
 virtual ~MyThread();
 virtual void Run(void) = 0;

 bool  Create(MyThread* thread);

 unsigned long  GetThreadID(void){return m_ThreadID;}

protected:
 static void*  ThreadRoutine(void*);

private:
 pthread_t*  m_pThread;
 unsigned long  m_ThreadID;

};

#endif /* MYTHREAD_H_ */