#include <pthread.h>
#include <stdio.h>
#include <atomic>
#include <iostream>

#define NUM_THREADS 10
#define NUM_INCREMENT 1000000

//std::atomic <long> cnt_global(0);
long cnt_global = 0;

void* thread_func(void* arg)
{
  long cnt_local = 0;

  for (int i = 0; i < NUM_INCREMENT; i++) {
    cnt_global++;
    cnt_local++;
  }

  return (void*)cnt_local;
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
  long ret;
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], (void**)&ret);
    printf("thread %ld: local count -> %ld\n", threads[i], ret);
  }
  printf("global count -> %ld\n", cnt_global);
  //std::cout << "global count -> " << cnt_global << std::endl;

  return 0;
}
