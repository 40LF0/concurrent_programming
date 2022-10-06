template<typename T>
class StampedSnap{
	public:
	long stamp;
	T value;
	T *snap;
	StampedSnap(T val);
	StampedSnap(long label,T val,T* snp);
	StampedSnap();
};

template<typename T>
class WFSnapshot {
	private:
	StampedSnap<T>** a_table;
	int len;
	StampedSnap<T>** collect();	
	

	public:
	WFSnapshot(int capacity, T init);
	
	void update(T value,int thread_id);

	T* scan();

};

