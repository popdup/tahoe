#ifndef DETAILJOB_H_
#define DETAILJOB_H_

#include "BaseJob.h"
#include <stdio.h>
#include <unistd.h>

class DetailJob: public BaseJob {
public:
 DetailJob();
 virtual ~DetailJob();

 void Run(void* jobdata){
  printf("this is the job %d\n",*(int*)jobdata);
	sleep(10);
 }
};

#endif /* DETAILJOB_H_ */
