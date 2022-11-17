#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <cassert>

#define NUM_THREADS 16
#define NUM_WORK 100000



class node{
  public:
  int flag;
  node* next;
  node() : flag(1), next(nullptr)
  {

  }
  ~node(){
    
  }
};

int cnt_global;
int gap_[128];
int object_tas;
int gap__[128];
node* tail = NULL;

void* thread_func(void* arg)
{
  long cnt_local = 0;

  for (int i = 0; i < NUM_WORK; i++) {
    node* new_node = new node;
    int gap[128];
    //lock(&object_tas);
    //while(__sync_lock_test_and_set(&object_tas,1)==1){}
    
    while(__sync_lock_test_and_set(&object_tas,1)==1){}
    node* prev = __sync_lock_test_and_set(&tail,new_node);
    __sync_synchronize();
    object_tas = 0;
    __sync_synchronize();
    assert(prev != new_node);

    int gap__[128];
    if(prev != NULL){
      while(prev->flag == 1){}
      delete prev;
    }
    assert(new_node->flag == 1);
    // critical section start
    cnt_global++;
    // critical section end
    
    while(__sync_lock_test_and_set(&object_tas,1)==1){}
    new_node->flag = 0;
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
