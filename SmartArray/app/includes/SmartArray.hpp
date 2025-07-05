#ifndef SMART_ARRAY_HPP
#define SMART_ARRAY_HPP

#include <fstream>
#include <iostream>
#include <handlers\ErrorHandler.hpp>

#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__

#include <mach-o/dyld.h>
#include <climits>

#elif
#include <unistd.h>
#endif
	
	inline std::filesystem::path GetExeDirectory() {
#ifdef _WIN32
	// Windows specific
	wchar_t szPath[MAX_PATH];
	DWORD length = GetModuleFileNameW(NULL, szPath, MAX_PATH);
	if (length == 0 || length == MAX_PATH)
		return {}; // some error

	return std::filesystem::path(szPath).parent_path();
#elif __APPLE__
	char szPath[PATH_MAX];
	uint32_t bufsize = PATH_MAX;
	if (!_NSGetExecutablePath(szPath, &bufsize))
		return std::filesystem::path{ szPath }.parent_path() / ""; // to finish the folder path with (back)slash
	return {};  // some error
#else
	// Linux specific
	char szPath[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", szPath, PATH_MAX);
	if (count < 0 || count >= PATH_MAX)
		return {}; // some error
	szPath[count] = '\0';
#endif
}

#define FILENAME "preload_data.bin"

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
	void resize(unsigned cap);
	bool isFull() const;
	bool isEmpty() const;
	
	// Getters
	unsigned size() const;
	T& get(int index);

	// Setters
	void setSize(unsigned s);
	void clear();

	// Operators
	SmartArray<T>& operator=(const SmartArray<T>& other);
	friend ostream& operator<< <T>(ostream& os, const SmartArray<T>& ob);
	T& operator[](unsigned index);
	const T& operator[](unsigned index) const;

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
bool SmartArray<T>::isFull() const{
	return size_ == capacity_;
}

template <typename T>
bool SmartArray<T>::isEmpty() const{
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
const T& SmartArray<T>::operator[](unsigned index) const{
	if (index >= size_) {
		ErrorHandler::handler(ErrorHandler::INDEX_OUT_OF_RANGE);
		static const T dummy{};
		return dummy;
	}

	return dat_[index];
}

// File Methods
inline static std::filesystem::path GetFileDirectory(std::string filename) {
	std::filesystem::path exeDir = GetExeDirectory();
	std::filesystem::path filePath = exeDir / ".." / ".." / "app" / "files" / filename;
	filePath = std::filesystem::weakly_canonical(filePath);
	
	return filePath;
}

/*
*	Writes arrays elements to a binary file
*	@param ob - given array
*	@param source - default file source for preloading data
*/
template <typename T>
inline static void save(const SmartArray<T>& ob, string source = FILENAME) {
	fstream file;
	file.open(GetFileDirectory(source), ios::out | ios::binary);

	if (!file.is_open()) {
		ErrorHandler::handler(ErrorHandler::OPENING_FILE_ERROR);
	}

	// Write array size
	unsigned current_size = ob.size();
	file.write(reinterpret_cast<const char*>(&current_size), sizeof(unsigned));
	
	for (unsigned i = 0; i < ob.size(); ++i) {
		serialize(file, ob[i]);
	}

	file.close();
}

template <typename T>
inline static void load(SmartArray<T>& ob, string source = FILENAME) {
	fstream file;
	file.open(GetFileDirectory(source), ios::in | ios::binary);

	if (!file.is_open()) {
		ErrorHandler::handler(ErrorHandler::OPENING_FILE_ERROR);
	}
	
	// Read array size
	unsigned new_size = 0;
	ob.clear();
	file.read(reinterpret_cast<char*>(&new_size), sizeof(unsigned));

	// Read all data
	for (unsigned i = 0; i < new_size; ++i) {
		T temp;
		deserialize(file, temp);
		ob.push(temp);
	}

	file.close();
}

#endif