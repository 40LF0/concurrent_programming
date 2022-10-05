#include "reg.h"
#include <gtest/gtest.h>
#include <iostream>
#include <stdio.h>
#include <cstddef>
#include <string>
#include <pthread.h>
#include <atomic>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

using namespace std::chrono;
using namespace std::this_thread;

#define NUM_THREADS 100



struct argu{
	long index;
	WFSnapshot<int>* p;
};

int intAtomic = 0;

void* ThreadFunc(void* arg) {
	long cnt = 0;
  struct argu* st = (struct argu*) arg;
  int index = st->index;
	WFSnapshot<int>* wf =st->p;
	/// random updating start!
	int val = 0;	
	while(cnt < 100000000){
		//wf->update(val,index);// this makes this thread killed
		cnt ++;
	}
	return (void*)cnt;
}

TEST(atomic_snapshot_Test, atomic_snap_shot_Initialization) {
	WFSnapshot<int>* wf = new WFSnapshot<int>(NUM_THREADS,1);

  pthread_t threads[NUM_THREADS];

  //auto start = high_resolutio n_clock::now();
  // create threads
  for (long i = 0; i < NUM_THREADS; i++) {
		struct argu* arg = new argu;
		arg-> index = i;
		arg-> p = wf;
    if (pthread_create(&threads[i], 0, ThreadFunc, (void*)arg) < 0) {
      printf("error: pthread_create failed!\n");
    }
  }
	//TIME:
  //auto stop = high_resolution_clock::now();
	//auto s = duration_cast<seconds>(stop - start);
	//if(s.count() >= 60){
	//	intAtomic++;
	//}
	//else goto TIME;

	//sleep_until(system_clock::now() + seconds(60));
	//initAtomic++;

  // wait for the threads to terminate
  long ret;
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], (void**)&ret);
    printf("thread%d %ld: local count -> %ld\n",i ,threads[i],ret);
  }
  //printf("global count -> %ld\n", cnt_global);
  //std::cout << "global count -> " << cnt_global << std::endl;
	
	
	
}
