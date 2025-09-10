#ifndef SMART_ARRAY_HPP
#define SMART_ARRAY_HPP

#include <fstream>
#include <iostream>
#include <handlers/ErrorHandler.hpp>

template <typename T>
class SmartArray;

template <typename T>
std::ostream& operator<<(std::ostream& os, const SmartArray<T>& ob);

/**
 * @brief A dynamic array template class similar to std::vector.
 *
 * Provides methods to add, remove, access, and manipulate elements.
 * Automatically manages memory and can grow when full.
 *
 * @tparam T Type of elements stored in the array.
 */
template <typename T>
class SmartArray {
	T* dat_ = nullptr;
	unsigned size_;
	unsigned capacity_;

public:
	/** @brief Default constructor. Initializes array with default capacity (5). */
	SmartArray();

	/** @brief Constructor with specified capacity.
	*  @param cap Initial capacity of the array.
	*/
	SmartArray(unsigned cap);

	/** @brief Copy constructor.
	*  @param ob Another SmartArray to copy from.
	*/
	SmartArray(const SmartArray& ob);

	/** @brief Destructor. Frees allocated memory. */
	~SmartArray();

	// Methods
	/** @brief Adds an element to the end of the array, reallocates if full.
	*  @param elem Element to add.
	*  @return 0 on success.
	*/
	int push(const T& elem);

	/** @brief Removes and returns the last element from the array.
	*  @return Last element or default T{} if array is empty.
	*/
	T pop();

	/** @brief Resizes the array to new capacity.
	 *  @param cap New capacity.
	 */
	void resize(unsigned cap);

	/** @brief Prints all elements to std::cout.
	*  @return 0 on success, 2 if array is empty.
	*/
	int printAll();

	/** @brief Checks if the array is full.
	*  @return true if full, false otherwise.
	*/
	bool isFull() const;

	/** @brief Checks if the array is empty.
	*  @return true if empty, false otherwise.
	*/
	bool isEmpty() const;

	// Getters
	/** @brief Returns the current number of elements.
	*  @return Number of elements.
	*/
	unsigned size() const;

	/** @brief Returns reference to element at specified index.
	*  @param index Index of element.
	*  @return Reference to element.
	*/
	T& get(int index);

	// Setters
	/** @brief Sets the size of the array manually.
	*  @param s New size.
	*/
	void setSize(unsigned s);

	/** @brief Clears all elements from the array. */
	void clear();

	// Operators
	/** @brief Assignment operator.
	*  @param other Another SmartArray to assign from.
	*  @return Reference to this SmartArray.
	*/
	SmartArray<T>& operator=(const SmartArray<T>& other);

	/** @brief Output stream operator. Prints all elements.
	*  @param os Output stream.
	*  @param ob SmartArray to print.
	*  @return Reference to the output stream.
	*/
	friend std::ostream& operator<< <T>(std::ostream& os, const SmartArray<T>& ob);

	/** @brief Access element by index (non-const).
	*  @param index Index of element.
	*  @return Reference to element.
	*/
	T& operator[](unsigned index);

	/** @brief Access element by index (const).
	*  @param index Index of element.
	*  @return Const reference to element.
	*/
	const T& operator[](unsigned index) const;

private:
	/** @brief Allocates memory for the array based on current capacity. */
	void alloc();

	/** @brief Reallocates array to new capacity.
	*  @param cap New capacity.
	*/
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
int SmartArray<T>::push(const T& elem) {
	if (isFull()) {
		reallocate(capacity_ * 2);
	}

	dat_[size_] = elem;
	size_++;

	return 0;
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
int SmartArray<T>::printAll() {
	if (isEmpty()) {
		ErrorHandler::handler(ErrorHandler::STACK_IS_EMPTY);
		return 2;
	}

	for (unsigned i = 0; i < size_; ++i) {
		std::cout << dat_[i] << std::endl;
	}

	return 0;
}

template <typename T>
bool SmartArray<T>::isFull() const {
	return size_ == capacity_;
}

template <typename T>
bool SmartArray<T>::isEmpty() const {
	return size_ == 0;
}

template <typename T>
unsigned SmartArray<T>::size() const {
	return size_;
}

template <typename T>
T& SmartArray<T>::get(int index) {
	return dat_[index];
}

template <typename T>
void SmartArray<T>::setSize(unsigned s) {
	size_ = s;
}

template <typename T>
void SmartArray<T>::clear() {
	size_ = 0;
}

template <typename T>
void SmartArray<T>::resize(unsigned cap) {
	reallocate(cap);
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
	catch (std::bad_alloc& ex) {
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
std::ostream& operator<<(std::ostream& os, const SmartArray<T>& ob) {
	if (ob.isEmpty()) {
		ErrorHandler::handler(ErrorHandler::STACK_IS_EMPTY);
		return os;
	}

	for (unsigned i = 0; i < ob.size_; ++i) {
		os << ob.dat_[i] << std::endl;
	}
	return os;
}

template <typename T>
T& SmartArray<T>::operator[](unsigned index) {
	if (index >= size_) {
		ErrorHandler::handler(ErrorHandler::INDEX_OUT_OF_RANGE);
		static T dummy{};
		return dummy;
	}

	return dat_[index];
}

template <typename T>
const T& SmartArray<T>::operator[](unsigned index) const {
	if (index >= size_) {
		ErrorHandler::handler(ErrorHandler::INDEX_OUT_OF_RANGE);
		static const T dummy{};
		return dummy;
	}

	return dat_[index];
}

#endif