#ifndef BASEJOB_H_
#define BASEJOB_H_

#include "MyThread.h"

class BaseJob {
public:
 BaseJob();
 virtual ~BaseJob();

 MyThread*  GetWorkThread(void){return m_pWorkThread;}
 void   SetWorkThread(MyThread* pWorkThread){m_pWorkThread = pWorkThread;}

 virtual void Run(void* ptr) = 0;
private:
 MyThread* m_pWorkThread;
};

#endif /* BASEJOB_H_ */