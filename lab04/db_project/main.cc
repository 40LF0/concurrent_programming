#include "bpt.h"

#include <iostream>
#include <stdio.h>
#include <cstddef>
#include <string>
#include <pthread.h>
#include <chrono>
#include <stdlib.h>
#include <string.h>
#include <atomic>


using namespace std::chrono;

struct argu{
	long index;
	WFSnapshot<int>* p;
};

long* thread_ret;
std::atomic<int> counter(0);

void* ThreadFunc(void* arg) {
 	struct argu* st;
	st = (struct argu*) arg;
 	int index = st->index;
	WFSnapshot<int>* wf =st->p;
	thread_ret[index] = 0;
	/// random updating start!
	auto start = system_clock::now();
	while(1){
		int val = rand();
		wf->update(val,index);// this makes this thread killed
		thread_ret[index]++;
		auto now = system_clock::now();
		auto duration = duration_cast<seconds>(now -start);
		if(duration.count() >= 10){
			return 0;
		}
	}
	return 0;
}

int main(int argc,char** argv) {
	//scanf("%d", &NUM_THREAD);
	if(argc != 2){
		printf("error\n");
		return -1;
	}
	int NUM_THREAD = atoi(argv[1]);
  pthread_t threads[NUM_THREAD];

				// Create atomic_register
	WFSnapshot<int>* wf = new WFSnapshot<int>(NUM_THREAD,1);
	thread_ret = new long[NUM_THREAD];
        // Create threads to work
  for (long i = 0; i < NUM_THREAD; i++) {
    struct argu* arg = new argu;
    arg-> index = i;
    arg-> p = wf; 

		


		if (pthread_create(&threads[i], 0, ThreadFunc, (void*)arg) < 0) {
      printf("pthread_create error!\n");
        return 0;
    }
		
  }



        // Wait threads end
  long cnt = 0;
  for (int i = 0; i < NUM_THREAD; i++) {
    pthread_join(threads[i], NULL);
    cnt += thread_ret[i];
  }
  printf("total updates %ld\n",cnt);
  

  return 0;
}

