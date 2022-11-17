#include <gtest/gtest.h>
#include "atomic_snap_shot.h"




/// Tests class StampedSnap<int>
/// creating StampedSnap<int> object
TEST(StampedSnapTest, initalize_test) {
	int i = 1;
	long label = 184168514;
	int** snap = new int*[10];
	for(int j = 0 ; j < 10 ; j ++){
		snap[j] = new int(j*19);
	}
	printf("he\n");
	// create object 
	StampedSnap<int> a(i,10);
	StampedSnap<int> b(label,i,snap,10);
	StampedSnap<int> c;
	
	// test wheather creating object works as intended

	EXPECT_EQ(a.value,i);
	for(int j = 0 ; j < 10 ; j++){
		EXPECT_EQ(*a.snap[j],i);
	}

	EXPECT_EQ(b.value,i);
	EXPECT_EQ(b.stamp,label);
	for(int i = 0 ; i < 10 ; i++){
		EXPECT_EQ(*(b.snap[i]),*snap[i]);
	}
	//class StampedSnap's template, c's value is not initalized yet
	//EXPECT_EQ(c.value,0);
	// we should care about it
	EXPECT_EQ(c.stamp,0);
	EXPECT_TRUE(c.snap==0);

}
/// Tests class WFSnapshot<int>
/// creating WFSnapshot<int> object
TEST(WFSnapshotTest, init_test) {
	int capacity = 10;
	int init = -1;

	WFSnapshot<int> a(capacity,init);
	// test WFSnapshot class
	// test update,scan operation in sequence situation
	for(int i = 0 ; i < capacity ; i++){
		a.update(i,i);
		int ** arr = a.scan(i);
		for(int j = 0 ; j <= i ; j++){
			EXPECT_EQ(*arr[j],j);
		}	
		for(int k = i+1 ; k < capacity ; k++){
			EXPECT_EQ(*arr[k],init);
		}
	}
}






/*
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
*/
/*
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

*/
