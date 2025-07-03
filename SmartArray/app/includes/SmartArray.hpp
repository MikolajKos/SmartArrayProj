#ifndef SMART_ARRAY_HPP
#define SMART_ARRAY_HPP

#include <iostream>
#include <handlers\ErrorHandler.hpp>

using namespace std;

template <typename T>
class SmartArray {
	T* dat_ = nullptr;
	unsigned size_;
	unsigned capacity_;

public:
	SmartArray();
	SmartArray(unsigned cap);
	SmartArray(const SmartArray& ob);
	~SmartArray();

	// Methods
	bool push(const T& elem);
	T pop();

	// Operators
	SmartArray<T>& operator=(const SmartArray<T>& other);

private:
	void alloc();
	void realloc();
};


// Implementation

template <typename T>
SmartArray<T>::SmartArray() : size_(0), capacity_(5) {
	alloc();
}

template <typename T>
SmartArray<T>::SmartArray(unsigned cap) : size_(0), capacity_(cap) {
	alloc();
}

template <typename T>
SmartArray<T>::SmartArray(const SmartArray& ob) {
	capacity_ = ob.capacity_;
	size_ = ob.size_;
	alloc();

	for (unsigned i = 0; i < size_; ++i) {
		dat_[i] = ob.dat_[i];
	}
}

template <typename T>
SmartArray<T>::~SmartArray() {
	delete[] dat_;
	dat_ = nullptr;
}

template <typename T>
void SmartArray<T>::alloc() {
	if (dat_) {
		delete[] dat_;
		dat_ = nullptr;
	}

	try {
		dat_ = new T[capacity_];
	}
	catch (bad_alloc& ex) {
		ErrorHandler::handler(ErrorHandler::MEM_ALLOC_ERROR, ex.what());
	}
}

// Operators
template <typename T>
SmartArray<T>& SmartArray<T>::operator=(const SmartArray<T>& other) {
	T* new_dat = nullptr;
	
	if (other.dat_) {
		new_dat = new T[other.capacity_];

		for (unsigned i = 0; i < size_; ++i) {
			new_dat[i] = other.dat_[i];
		}
	}

	delete[] dat_;

	capacity_ = other.capacity_;
	size_ = other.size_;
	dat_ = new_dat;

	return *this;
}

#endif