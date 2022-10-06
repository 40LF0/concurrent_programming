#include <iostream>
#include <stdio.h>
#include <cstddef>
#include <string>
#include <pthread.h>
#include <chrono>
#include <stdlib.h>
#include <string.h>
#include <atomic>
/////////////////////////////////////////////////////////
template<typename T>
class StampedSnap{
	public:
	long stamp;
	T value;
	T *snap;
	StampedSnap(T val){
		stamp =0;
		value = val;
		snap = 0;
	}
	StampedSnap(long label,T val,T* snp){
		stamp = label;
		value = val;
		snap = snp;
	}
	StampedSnap(){
		stamp = 0;
		snap = 0;
	}

	
};

template<typename T>
class WFSnapshot {
	private:
	StampedSnap<T>** a_table;
	int len;
	StampedSnap<T>** collect(){
		StampedSnap<T>** copy =(StampedSnap<T>**) new StampedSnap<T>*[len];
		for (int j = 0; j < len; j++) {
			copy[j] = new StampedSnap<T>(a_table[j]->stamp,a_table[j]->value,a_table[j]->snap);  
		}
		return copy;
	}	
	

	public:
	WFSnapshot(int capacity, T init) {
		a_table = (StampedSnap<T>**) new StampedSnap<T>*[capacity];
		this->len = capacity;
		for (int i = 0; i < capacity; i++) {
			a_table[i] = new StampedSnap<T>(init); 
		}
	}
	
	void update(T value,int thread_id){
		//printf("u v:%d t:%d\n");
		int id = thread_id;
		T* snap = scan();
		StampedSnap<T>* oldVal = a_table[id];
		StampedSnap<T>* newVal = new StampedSnap<T>(oldVal->stamp+1,value,snap);
		delete oldVal;
		a_table[id] = newVal;
	}

	T* scan(){
		StampedSnap<T>** oldcopy;
		StampedSnap<T>** newcopy;
		bool *moved = new bool[len];

		for(int j = 0 ; j  < len ; j ++){
			moved[j] = false;
		}

		oldcopy = collect();

		COLLECT:
		newcopy = collect();
		for(int j = 0 ; j  < len ; j ++){
			if(oldcopy[j]->stamp != newcopy[j]->stamp){
				if(moved[j]) return oldcopy[j]->snap;
				else {
					moved[j] = true;
					oldcopy = newcopy;
					    for (int j = 0; j < len; j++) {
								delete oldcopy[j];
					    }

					goto COLLECT;
				}
			}
		}	
    
    for (int j = 0; j < len; j++) {
			delete oldcopy[j];
		}   
	  
		oldcopy = newcopy;		
		T* result = new T[len];
		for(int j = 0 ; j < len ; j ++){
			result[j] = newcopy[j]->value;
		} 
		delete oldcopy;
		return result;
	}

};

///////////////////////////////////////////////////////////////////


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

