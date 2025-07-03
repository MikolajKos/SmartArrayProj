#ifndef SMART_ARRAY_HPP
#define SMART_ARRAY_HPP

#include <iostream>
#include <handlers\ErrorHandler.hpp>

using namespace std;

template <typename T>
class SmartArray;

template <typename T>
ostream& operator<<(ostream& os, const SmartArray<T>& ob);

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
	bool isFull();
	bool isEmpty();

	// Operators
	SmartArray<T>& operator=(const SmartArray<T>& other);
	friend ostream& operator<< <T>(ostream& os, const SmartArray<T>& ob);

private:
	void alloc();
	void reallocate(unsigned cap);
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
bool SmartArray<T>::push(const T& elem) {
	if (isFull()) {
		reallocate(capacity_ * 2);
	}

	dat_[size_] = elem;
	size_++;

	return true;
}

template <typename T>
T SmartArray<T>::pop() {
	if (isEmpty()) {
		ErrorHandler::handler(ErrorHandler::STACK_IS_EMPTY);
		return T{};
	}

	return dat_[--size_];
}

template <typename T>
bool SmartArray<T>::isFull() {
	return size_ == capacity_;
}

template <typename T>
bool SmartArray<T>::isEmpty() {
	return size_ == 0;
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

template <typename T>
void SmartArray<T>::reallocate(unsigned cap) {
	T* new_dat = new T[cap];

	for (unsigned i = 0; i < size_; ++i) {
		if (i >= cap) {
			break;
		}
		new_dat[i] = dat_[i];
	}

	delete[] dat_;

	dat_ = new_dat;
	capacity_ = cap;
	if (cap < size_) {
		size_ = cap;
	}
}

// Operators
template <typename T>
SmartArray<T>& SmartArray<T>::operator=(const SmartArray<T>& other) {
	T* new_dat = nullptr;
	
	if (other.dat_) {
		new_dat = new T[other.capacity_];

		for (unsigned i = 0; i < other.size_; ++i) {
			new_dat[i] = other.dat_[i];
		}
	}

	delete[] dat_;

	capacity_ = other.capacity_;
	size_ = other.size_;
	dat_ = new_dat;

	return *this;
}

template <typename T>
ostream& operator<<(ostream& os, const SmartArray<T>& ob) {
	for (unsigned i = 0; i < ob.size_; ++i) {
		os << ob.dat_[i] << std::endl;
	}
	return os;
}

#endif