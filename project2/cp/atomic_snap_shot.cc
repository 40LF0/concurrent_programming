#include "atomic_snap_shot.h"


StampedSnap::StampedSnap(T val){
	stamp =0;
	value = val;
	snap = 0;
}

tampedSnap::StampedSnap(long label,T val,T* snp){
	stamp = label;
	value = val;
	snap = snp;
}
StampedSnap::StampedSnap(){
	stamp = 0;
	snap = 0;
}

WFSnapshot::StampedSnap<T>** collect(){
	StampedSnap<T>** copy =(StampedSnap<T>**) new StampedSnap<T>*[len];
	for (int j = 0; j < len; j++) {
		copy[j] = new StampedSnap<T>(a_table[j]->stamp,a_table[j]->value,a_table[j]->snap);  
	}
	return copy;
}	
	
WFSnapshot::WFSnapshot(int capacity, T init) {
	a_table = (StampedSnap<T>**) new StampedSnap<T>*[capacity];
	this->len = capacity;
	for (int i = 0; i < capacity; i++) {
		a_table[i] = new StampedSnap<T>(init); 
	}
}
	
void WFSnapshot::update(T value,int thread_id){
	//printf("u v:%d t:%d\n");
	int id = thread_id;
	T* snap = scan();
	StampedSnap<T>* oldVal = a_table[id];
	StampedSnap<T>* newVal = new StampedSnap<T>(oldVal->stamp+1,value,snap);
	delete oldVal;
	a_table[id] = newVal;
}

T* WFSnapshot::scan(){
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