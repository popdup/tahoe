#include "MyThreadPool.h"
#include <stdio.h>

MyThreadPool::MyThreadPool() {
 // TODO Auto-generated constructor stub
 m_MaxNum = 10;
 m_InitNum = 5;
 m_BusyList.clear();
 m_IdleList.clear();
 for(int i=0; i<m_InitNum; i++){
  MyWorkThread* thread = new MyWorkThread();
  thread->SetThreadPool(this);
  AppendToIdleList(thread);
  thread->Create(thread);
 }
}

MyThreadPool::MyThreadPool(int InitNum) {
 assert(InitNum>=2 && InitNum<=20);
 m_MaxNum = 10;
 m_InitNum = InitNum;
 m_BusyList.clear();
 m_IdleList.clear();
 for(int i=0; i<m_InitNum; i++){
  MyWorkThread* thread = new MyWorkThread();
  thread->SetThreadPool(this);
  AppendToIdleList(thread);
  thread->Create(thread);
 }
}

MyThreadPool::~MyThreadPool() {
 // TODO Auto-generated destructor stub
}

MyWorkThread* MyThreadPool::GetIdleThread(void){
 while(m_IdleList.size() <= 0){
  usleep(10);
 }
 m_IdleMutex.Lock();
 if(m_IdleList.size()>0){
  MyWorkThread* thread = (MyWorkThread*)m_IdleList.front();
  m_IdleMutex.Unlock();
  return thread;
 }
 m_IdleMutex.Unlock();
 return NULL;
}

//add a thread into idle list
void MyThreadPool::AppendToIdleList(MyWorkThread* thread){
 m_IdleMutex.Lock();
 m_IdleList.push_back(thread);
 m_IdleMutex.Unlock();
}

//move the idle thread from idle list to busy list
void MyThreadPool::MoveToBusyList(MyWorkThread* idlethread){
 printf("MoveToBusyList\n");
 m_BusyMutex.Lock();
 m_BusyList.push_back(idlethread);
 m_BusyMutex.Unlock();

 m_IdleMutex.Lock();
 vector<MyWorkThread*>::iterator pos;
 pos = find(m_IdleList.begin(), m_IdleList.end(), idlethread);
 if(pos != m_IdleList.end()){
  m_IdleList.erase(pos);
 }
 m_IdleMutex.Unlock();
}

//move the busy thread from busy list to idle list
void MyThreadPool::MoveToIdleList(MyWorkThread* busythread){
 printf("MoveToIdleList\n");
 m_IdleMutex.Lock();
 m_IdleList.push_back(busythread);
 m_IdleMutex.Unlock();

 m_BusyMutex.Lock();
 vector<MyWorkThread*>::iterator pos;
 pos = find(m_BusyList.begin(), m_BusyList.end(), busythread);
 if(pos != m_BusyList.end()){
  m_BusyList.erase(pos);
 }
 m_BusyMutex.Unlock();
}

void MyThreadPool::CreateIdleThread(int num){
 printf("CreateIdleThread:%d\n", num);
 for(int i=0; i<num; i++){
  MyWorkThread* thread = new MyWorkThread();
  thread->SetThreadPool(this);
  AppendToIdleList(thread);
  thread->Create(thread);
 }
}

void MyThreadPool::Run(BaseJob* job, void* jobdata){
 assert(job != NULL);
 while(GetBusyNum() >= m_MaxNum) {
  usleep(10);
 }
// if(GetAllNum() < m_MaxNum){
//  CreateIdleThread(m_MaxNum-GetAllNum());
// }
 MyWorkThread* idlethread = GetIdleThread();
 if(idlethread != NULL){
  MoveToBusyList(idlethread);
  idlethread->SetThreadPool(this);
  job->SetWorkThread(idlethread);
  idlethread->SetJob(job, jobdata);
 }
}