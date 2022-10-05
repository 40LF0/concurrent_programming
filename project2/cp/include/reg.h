#include <iostream>
#include <stdio.h>
#include <cstddef>
#include <string>

/*
template<typename T>
class Register{
  public:
  virtual T read() = 0;
  virtual void write(T v); 
}
*/
/*
class SafeBooleanMRSWRegister : public Register<bool>{
  protected:
  bool s_table[]; // array of safe SRSW registers
    
  public:
  SafeBooleanMRSWRegister(int capacity){
    s_table = new bool[capacity];
  }
  bool read(){
		extern int thread_id;
    return s_table[thread_id];
  }
  void write(bool x){
		int length = sizeof(s_table)/sizeof(bool);
		for(int i = 0 ; i < length ; i++){
			s_table[i] = x;
		}
  }
}
*/
/*
class RegBooleanMRSWRegister : public Register<bool>{
  protected:
  thread_local bool last = false;
  bool s_value = false; // safe MRSW registers
    
  public:
  bool read(){
		return s_value;
  }
  void write(bool x){
		if(x != last){
			last = x;
			s_value = x;
    }
  }
}
*/
/*
template<typename T>
class StampedValue{
	public:
	long stamp;
	T value;
	StampedValue(T init){
		stamp = 0;
		value = init;
	}
	StampedValue(long stmp,T val){
		stamp = stmp;
		value = val;
	}

	static StampedValue max(StampedValue x,StampedValue y){
		if(x.stamp>y.stamp){
			return x;
		}
		else{
			return y;
		}
	}	

	static StampedValue MIN_VALUE = new StampedValue(NULL);
	
}
*/


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
		int len = capacity;
		for (int i = 0; i < capacity; i++) {
			a_table[i] = new StampedSnap<T>(init); 
		}
	}
	
	void update(T value,int thread_id){
		int id = thread_id;
		T* snap = scan();
		StampedSnap<T>* oldVal = a_table[id];
		StampedSnap<T>* newVal = new StampedSnap<T>(oldVal->stamp+1,value,snap);
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
					goto COLLECT;
				}
			}
		}				
		T* result = new T[len];
		for(int j = 0 ; j < len ; j ++){
			result[j] = newcopy[j]->value;
		} 
		return result;
	}

};


