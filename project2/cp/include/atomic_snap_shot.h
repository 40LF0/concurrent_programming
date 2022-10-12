#include <iostream>
#include <stdio.h>
#include <cstddef>
#include <string>
#include <pthread.h>
#include <chrono>    /// to measure time
#include <stdlib.h>
#include <string.h>
#include <atomic>    /// for main function to count updating.



template<typename T>
class StampedSnap{
	/// Definition of thread local snapshot
	/// only one thread can modify this class object.
	/// other thread only can read members' value.
	public:
	/// stamp is time value for snap. stamp means number of thread local updates.
	/// other thread will notice modification by different stamp value.
	long stamp;
	/// thread local value.
	T value;
	/// thread local snapshot which is used for other thread's scan.
	T **snap;
	/// len is number of thread which cooperative with include it's own thread.
	int len;
	StampedSnap(T val,int leng);
	StampedSnap(long label,T val,T** snp,int leng);
	StampedSnap();
	~StampedSnap();
};

template<typename T>
class WFSnapshot {
	/// Definition of wait free atomic snapshot
	private:
	/// a_table is array of thread local StampedSnap
	/// a_table help to access each thread local stamp,value and snap.
	StampedSnap<T>** a_table;
	/// len is number of thread which WFSnapshot class object should deal with
	int len;
	/// collect every thread local StampedSnap object.
	void collect(int thread_id,int index);	

	/// we need dummy for collecting a_table!
	/// we preallocate 3 dummy for each thread!
	/// 1st dummy is stored in buffercopy1
	/// 2nt dummy is stored in buffercopy2
	/// 3rd dummy is stored in buffercopy3
	/// buffercopy is entry array for buffercopy1,buffercopy2,and buffercopy3

	// if you want to access thread i 2rd dummy this process will helpful
	/*
	StampedSnap<T>*** entry = buffercopy[1];
	StampedSnap<T>** dummy2_for_i = entry[i];
	//or just
	StampedSnap<T>** dummy2_for_i = buffercopy2[i];
	*/
	
	StampedSnap<T>**** buffercopy;
	StampedSnap<T>*** buffercopy1;
	StampedSnap<T>*** buffercopy2;
	StampedSnap<T>*** buffercopy3;

	/// we need dummy for return snap for collect function.
	/// we preallocate dummy snap for each thread.

	T*** arr_buf;


	public:
	WFSnapshot(int capacity, T init);
	~WFSnapshot();
	void update(T value,int thread_id);
	T** scan(int thread_id);

};


template<typename T>
StampedSnap<T>::StampedSnap(T val,int leng){
	stamp =0;
	value = val;
	len = leng;
	snap = new T*[len];
	for(int i = 0 ; i < len ; i++){
		snap[i] = new T(val);
	}
}

template<typename T>
StampedSnap<T>::StampedSnap(long label,T val,T** snp,int leng){
	stamp = label;
	value = val;
	len = leng;
	snap = new T*[len];
	for(int i = 0 ; i < len ; i++){
		snap[i] = new T( *snp[i]);
	}
}

template<typename T>
StampedSnap<T>::StampedSnap(){
	stamp = 0;
	snap = 0;
	len = 0;
}
template<typename T>
StampedSnap<T>::~StampedSnap(){
	for(int i = 0 ; i < len ; i ++){
		delete snap[i];
	}
	delete[] snap;
}



template<typename T>
WFSnapshot<T>::WFSnapshot(int capacity, T init) {
	a_table = new StampedSnap<T>*[capacity];
	this->len = capacity;
	buffercopy = new StampedSnap<T>***[3];
	buffercopy1 = buffercopy[0];
	buffercopy2 = buffercopy[1];
	buffercopy3 = buffercopy[2];
	
	buffercopy1 = new StampedSnap<T>**[capacity];
	buffercopy2 = new StampedSnap<T>**[capacity];
	buffercopy3 = new StampedSnap<T>**[capacity];
	
	arr_buf = new T**[capacity];
	

	for (int i = 0; i < capacity; i++) {
		a_table[i] = new StampedSnap<T>(init,capacity);
		buffercopy1[i] = (StampedSnap<T>**) new StampedSnap<T>*[capacity];
		buffercopy2[i] = (StampedSnap<T>**) new StampedSnap<T>*[capacity];
		buffercopy3[i] = (StampedSnap<T>**) new StampedSnap<T>*[capacity];
		arr_buf[i] = new T*[capacity];

		for (int j = 0; j < capacity; j++) {
			arr_buf[i][j] = new T(init);
			buffercopy1[i][j] = new StampedSnap<T>(init,capacity);  
			buffercopy2[i][j] = new StampedSnap<T>(init,capacity);  
			buffercopy3[i][j] = new StampedSnap<T>(init,capacity);  
		}

	}



}

template<typename T>
WFSnapshot<T>::~WFSnapshot() {
	for (int i = 0; i < this->len; i++) {
		delete a_table[i]; 
	}
	delete[] a_table;

}
	
template<typename T>
void WFSnapshot<T>::update(T value,int thread_id){
	// update value with clean snapshot and stamp
	int id = thread_id;
	T** snap = scan(thread_id);
	
	a_table[id]->value = value;
	for(int i = 0 ; i < len ; i++){
		*(a_table[id]->snap[i]) = *(snap[i]);
	}
	a_table[id]->stamp++;

	//StampedSnap<T>* oldVal = a_table[id];
	//StampedSnap<T>* newVal = new StampedSnap<T>(oldVal->stamp+1,value,snap,len);
	//a_table[id] = newVal;

	//delete oldVal;
}

template<typename T>
void WFSnapshot<T>::collect(int thread_id,int index){
	/// collect a_table to a_table dummy!
	StampedSnap<T>** copy;

	// set entry to correct a_table dummy
	if(index == 0){
		copy = buffercopy1[thread_id];
	}
	else if(index == 1){
		copy = buffercopy2[thread_id];
	}
	else if(index == 2){
		copy = buffercopy3[thread_id];
	}
	else{
		printf("error,buffercopy\n");
		return;
	}

	// collect a_table to dummy
	for (int j = 0; j < len; j++) {
		copy[j]->stamp = a_table[j]->stamp;
		copy[j]->value = a_table[j]->value;
		for(int i = 0 ; i < len ; i ++){
			*(copy[j]->snap[i]) = *(a_table[j]->snap[i]);
			/*
			BUG FIXED BY DUMMY
			// *(copy[j]->snap[i]) = *(a_table[j]->snap[i]); // problem

			StampedSnap<T>** a = a_table;
			StampedSnap<T>* b = a[j];
			T** c = b->snap;
			T* e = c[i];
			T d = *e;

			StampedSnap<T>** a_ = copy;
			StampedSnap<T>* b_ = a_[j];
			T** c_ = b_->snap;
			T*e_ = c_[i];
			*e_ = d;

			*/

		}
		copy[j]->len = a_table[j]->len;
	}
}	
/*
BUG FIXED BY DUMMY
int *p;
std::cout << p << std::endl; -> 0x56
p = new int(5);              
std::cout << p << std::endl; -> 0x505338
pointer value is less than 0xff means, intialize operation of pointer is not performed yet.
this problem occur when childe thread number is 25 to 40.

Hardware spec

processor	: 0
vendor_id	: GenuineIntel
cpu family	: 6
model		: 142
model name	: Intel(R) Core(TM) i5-8265U CPU @ 1.60GHz
stepping	: 11
cpu MHz		: 1800.001
cache size	: 6144 KB
physical id	: 0
siblings	: 1
core id		: 0
cpu cores	: 1
apicid		: 0
initial apicid	: 0
fpu		: yes
fpu_exception	: yes
cpuid level	: 22
wp		: yes
bogomips	: 3600.00
clflush size	: 64
cache_alignment	: 64
address sizes	: 39 bits physical, 48 bits virtual
*/

template<typename T>
T** WFSnapshot<T>::scan(int thread_id){
	/// scan for clean snapshot!

	// declare entry for a_table dummys
	StampedSnap<T>** copy1 = buffercopy1[thread_id];
	StampedSnap<T>** copy2 = buffercopy2[thread_id];
	StampedSnap<T>** copy3 = buffercopy3[thread_id];

	// delare entry for snap dummy 
	// later, this can be used as return value.
	T** result = arr_buf[thread_id];

	// This is bool array to check which thread local stamp is modified.
	bool* b_table = new bool[len]();
	


	collect(thread_id,0);

	collect(thread_id,1);

	for(int j = 0 ; j  < len ; j ++){
		if(copy1[j]->stamp != copy2[j]->stamp){
			// modification occur, try another collect!
			b_table[j] = true;
			goto COLLECT;
		}
	}	

	// we have clean snapshot!
	for(int j = 0 ; j < len ; j ++){
		*result[j] = copy2[j]->value;
	} 
	delete[] b_table;
	return result;
	

	COLLECT:
	collect(thread_id,2);
	for(int j = 0 ; j  < len ; j ++){
		if(copy2[j]->stamp != copy3[j]->stamp){
			// modification occur
			if(b_table[j] == true){
				// same thread local stamp is modified twice!
				// get clean snap from that thread!
				delete[] b_table;
				return copy2[j]->snap;
			}
			else{
				// new thread local stamp is modified
				// try another collect!
				b_table[j] = true;
				goto COLLECT2;

			}
		}
	}
	// we have clean snapshot!
	for(int j = 0 ; j < len ; j ++){
		*result[j] = copy3[j]->value;
	} 
	delete[] b_table;
	return result;

	COLLECT2:
	collect(thread_id,0);
	for(int j = 0 ; j  < len ; j ++){
		if(copy3[j]->stamp != copy1[j]->stamp){
			if(b_table[j] == true){
				// same thread local stamp is modified twice!
				// get clean snap from that thread!
				delete[] b_table;
				return copy3[j]->snap;
			}
			else{
				// new thread local stamp is modified
				// try another collect!
				b_table[j] = true;
				goto COLLECT3;

			}
		}
	}
	// we have clean snapshot!
	for(int j = 0 ; j < len ; j ++){
		*result[j] = copy1[j]->value;
	} 
	delete[] b_table;
	return result;

	COLLECT3:
	collect(thread_id,1);
	for(int j = 0 ; j  < len ; j ++){
		if(copy1[j]->stamp != copy2[j]->stamp){
			if(b_table[j] == true){
				// same thread local stamp is modified twice!
				// get clean snap from that thread!
				delete[] b_table;
				return copy1[j]->snap;
			}
			else{
				// new thread local stamp is modified
				// try another collect!
				b_table[j] = true;
				goto COLLECT;

			}
		}
	}
	// we have clean snapshot!
	for(int j = 0 ; j < len ; j ++){
		*result[j] = copy2[j]->value;
	} 
	delete[] b_table;
	return result;
}

