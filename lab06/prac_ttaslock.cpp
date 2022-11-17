#include <stdio.h>
#include <pthread.h>
#include <iostream>

#define NUM_THREADS 16
#define NUM_WORK 100000

int cnt_global;

int gap[128];
int object_tas;

void* thread_func(void* arg)
{
  long cnt_local = 0;

  for (int i = 0; i < NUM_WORK; i++) {
    //lock(&object_tas);
    while(1){
      while(object_tas == 1){}
      if(__sync_lock_test_and_set(&object_tas,1)==0){
        break;
      }
    }
    cnt_global++;
    object_tas = 0;
    __sync_synchronize();
    //unlock(&object_tas);
  }
}

int main(void)
{
  pthread_t threads[NUM_THREADS];

  // create threads
  for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&threads[i], 0, thread_func, NULL) < 0) {
      printf("error: pthread_create failed!\n");
      return 0;
    }
  }

  // wait for the threads to terminate
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  return 0;
}
