#ifndef SMARTARRAY_H
#define SMARTARRAY_H

template <typename T>
class SmartArray {
	T* data_;
	unsigned size_;
	unsigned capacity_;

public:
	SmartArray();
	SmartArray(unsigned cap);
	SmartArray(const SmartArray& ob);
	~SmartArray();

	//Methods
	bool push(const T& elem);
	T pop()

private:
	void alloc();
	void realloc();
};

#endif