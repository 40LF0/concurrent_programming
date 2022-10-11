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
	public:
	long stamp;
	T value;
	T **snap;
	int len;
	StampedSnap(T val,int leng);
	StampedSnap(long label,T val,T** snp,int leng);
	StampedSnap();
	~StampedSnap();
};

template<typename T>
class WFSnapshot {
	private:
	StampedSnap<T>** a_table;
	int len;
	void collect(int thread_id,int index);	

	StampedSnap<T>**** buffercopy;
	StampedSnap<T>*** buffercopy1;
	StampedSnap<T>*** buffercopy2;
	StampedSnap<T>*** buffercopy3;
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
	StampedSnap<T>** copy;
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


	for (int j = 0; j < len; j++) {
		copy[j]->stamp = a_table[j]->stamp;
		copy[j]->value = a_table[j]->value;
		for(int i = 0 ; i < len ; i ++){
			// *(copy[j]->snap[i]) = *(a_table[j]->snap[i]); // problem
			///*
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
			//*/

		}
		copy[j]->len = a_table[j]->len;
	}
}	
/*
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
	StampedSnap<T>** copy1 = buffercopy1[thread_id];
	StampedSnap<T>** copy2 = buffercopy2[thread_id];
	StampedSnap<T>** copy3 = buffercopy3[thread_id];
	T** result = arr_buf[thread_id];

	bool* b_table = new bool[len]();
	


	collect(thread_id,0);

	collect(thread_id,1);

	for(int j = 0 ; j  < len ; j ++){
		if(copy1[j]->stamp != copy2[j]->stamp){
			b_table[j] = true;
			goto COLLECT;
		}
	}	

	for(int j = 0 ; j < len ; j ++){
		*result[j] = copy2[j]->value;
	} 
	delete[] b_table;
	return result;
	

	COLLECT:
	collect(thread_id,2);
	for(int j = 0 ; j  < len ; j ++){
		if(copy2[j]->stamp != copy3[j]->stamp){
			if(b_table[j] == true){
				delete[] b_table;
				return copy2[j]->snap;
			}
			else{
				b_table[j] = true;
				goto COLLECT2;

			}
		}
	}

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
				delete[] b_table;
				return copy3[j]->snap;
			}
			else{
				b_table[j] = true;
				goto COLLECT3;

			}
		}
	}

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
				delete[] b_table;
				return copy1[j]->snap;
			}
			else{
				b_table[j] = true;
				goto COLLECT;

			}
		}
	}

	for(int j = 0 ; j < len ; j ++){
		*result[j] = copy2[j]->value;
	} 
	delete[] b_table;
	return result;
}


