#include <iostream>
#include <stdio.h>
#include <cstddef>
#include <string>
#include <pthread.h>
#include <chrono>
#include <stdlib.h>
#include <string.h>
#include <atomic>



template<typename T>
class StampedSnap{
	public:
	long stamp;
	T value;
	T *snap;
	int len;
	StampedSnap(T val,int leng);
	StampedSnap(long label,T val,T* snp,int leng);
	StampedSnap();
	~StampedSnap();
};

template<typename T>
class WFSnapshot {
	private:
	StampedSnap<T>** a_table;
	int len;
	StampedSnap<T>** collect();	
	

	public:
	WFSnapshot(int capacity, T init);
	~WFSnapshot();
	void update(T value,int thread_id);
	T* scan();

};


template<typename T>
StampedSnap<T>::StampedSnap(T val,int leng){
	stamp =0;
	value = val;
	len = leng;
	snap = new T[len];
	for(int i = 0 ; i < len ; i++){
		snap[i] = val;
	}
}

template<typename T>
StampedSnap<T>::StampedSnap(long label,T val,T* snp,int leng){
	stamp = label;
	value = val;
	len = leng;
	snap = new T[len];
	for(int i = 0 ; i < len ; i++){
		snap[i] = snp[i];
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
	delete[] snap;
}



template<typename T>
WFSnapshot<T>::WFSnapshot(int capacity, T init) {
	a_table = (StampedSnap<T>**) new StampedSnap<T>*[capacity];
	this->len = capacity;
	for (int i = 0; i < capacity; i++) {
		a_table[i] = new StampedSnap<T>(init,capacity); 
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
	//printf("u v:%d t:%d\n");
	int id = thread_id;
	T* snap = scan();
	StampedSnap<T>* oldVal = a_table[id];
	StampedSnap<T>* newVal = new StampedSnap<T>(oldVal->stamp+1,value,snap,len);
	///-> use preallocated datastructure;
	delete oldVal;
	a_table[id] = newVal;
	delete[] snap;
}

template<typename T>
StampedSnap<T>** WFSnapshot<T>::collect(){
	StampedSnap<T>** copy =(StampedSnap<T>**) new StampedSnap<T>*[len];
	for (int j = 0; j < len; j++) {
		copy[j] = new StampedSnap<T>(a_table[j]->stamp,a_table[j]->value,a_table[j]->snap,this->len);  
	}
	return copy;
}	

template<typename T>
T* WFSnapshot<T>::scan(){
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
			if(moved[j]){ 
				T* result = new T[len];
				for(int j = 0 ; j < len ; j ++){
					result[j] = oldcopy[j]->value;
				} 
				for (int j = 0; j < len; j++) {
					delete oldcopy[j];
				}
				delete[] oldcopy;	

				for (int j = 0; j < len; j++) {
					delete newcopy[j];
				}
				delete[] newcopy;

				delete[] moved;
				return result;
			}
			else {
				moved[j] = true;

				for (int j = 0; j < len; j++) {
					delete oldcopy[j];
				}
				delete[] oldcopy;	
				
				oldcopy = newcopy;
				goto COLLECT;
			}
		}
	}	
    
	for (int j = 0; j < len; j++) {
		delete oldcopy[j];
	}
	delete[] oldcopy;   
	  		
	T* result = new T[len];
	for(int j = 0 ; j < len ; j ++){
		result[j] = newcopy[j]->value;
	} 

	for (int j = 0; j < len; j++) {
		delete newcopy[j];
	}
	delete[] newcopy;	

	delete[] moved;

	return result;
}


