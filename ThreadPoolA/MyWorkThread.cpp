#include "MyWorkThread.h"
#include "MyThreadPool.h"
#include <string.h>
#include <stdio.h>

MyWorkThread::MyWorkThread() {
 // TODO Auto-generated constructor stub
 m_pJob = NULL;
 m_pJobdata = NULL;
 m_pThreadPool = NULL;
}

MyWorkThread::~MyWorkThread() {
 // TODO Auto-generated destructor stub
 if(m_pJob != NULL){
  delete m_pJob;
 }
 if(m_pJobdata != NULL){
  delete m_pJobdata;
 }
 m_pJob = NULL;
 m_pJobdata = NULL;
 m_pThreadPool = NULL;
}

void MyWorkThread::Run(){
 for(;true;usleep(10)){
  while(m_pJob == NULL){
   usleep(20);
  }
  m_pJob->Run(m_pJobdata);
  //finish the job
  m_pJob->SetWorkThread(NULL);
  m_pJob = NULL;
  m_pThreadPool->MoveToIdleList(this);
 }
}

void MyWorkThread::SetJob(BaseJob* job, void* jobdata){
 m_pJob = job;
 m_pJobdata = malloc(sizeof(jobdata));
 memcpy(m_pJobdata, jobdata, sizeof(jobdata));
// m_pJobdata = jobdata;
 printf("Thread %lu Run the job: %d\n",this->GetThreadID(), *(int*)m_pJobdata);
 m_pJob->SetWorkThread(this);
}

void MyWorkThread::SetThreadPool(MyThreadPool* threadpool){
 m_pThreadPool = threadpool;
}