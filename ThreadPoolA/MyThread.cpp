#include "MyThread.h"

MyThread::MyThread() {
 // TODO Auto-generated constructor stub
 m_pThread = new pthread_t;
}

MyThread::~MyThread() {
 // TODO Auto-generated destructor stub
 if(m_pThread != NULL){
  delete m_pThread;
 }
 m_pThread = NULL;
}

void* MyThread::ThreadRoutine(void* para){
 MyThread* thr = (MyThread*) para;
 thr->Run();
 return NULL;
}

bool MyThread::Create(MyThread* thread){
 int rs = pthread_create(m_pThread, NULL, ThreadRoutine, (void*)thread);
 m_ThreadID = *m_pThread;
 assert(rs == 0);
 return true;
}