#include <iostream>
#include "DetailJob.h"
#include "MyThreadPool.h"
using namespace std;

int main(int argc, char** argv)
{
	 MyThreadPool* tp = new MyThreadPool(5);
	 int i=0;
	 for(; i<50; i++)
	 {
	  DetailJob* job = new DetailJob();
	  tp->Run(job, &i);
	 }
	 sleep(10);
	 return 0;
}
