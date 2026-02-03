#ifndef SMART_ARRAY_IO_HPP
#define SMART_ARRAY_IO_HPP

#include <SmartArray.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <handlers/ErrorHandler.hpp>

#include <filesystem>

#ifdef _WIN32
       #include <windows.h>
#elif __APPLE__

       #include <mach-o/dyld.h>
       #include <climits>

#else
       #include <unistd.h>
       #include <climits>
#endif

/**
 * @brief Get the directory of the currently running executable.
 *
 * Works for Windows, macOS, and Linux platforms.
 *
 * @note This implementation is based on a solution from YouTube:
 *       https://www.youtube.com/watch?v=5ZADZsAH7XI&ab_channel=vlogize
 *
 * @return std::filesystem::path Path to the executable's directory.
 */
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
	return std::filesystem::path(szPath).parent_path();
#endif
}

#define FILENAME "preload_data.bin"

/**
 * @brief Template class for saving and loading SmartArray objects to/from binary files.
 *
 * @tparam T Type of elements stored in SmartArray.
 */
template <typename T>
class SmartArrayIO {
	/**
	* @brief Get the full path for a given filename relative to the executable.
	*
	* @param filename Name of the file
	* @return std::filesystem::path Full path to the file
	*/
	static std::filesystem::path GetFileDirectory(std::string filename);
public:
	/**
	* @brief Save a SmartArray to a binary file.
	*
	* @param ob SmartArray object to save
	* @param source Filename to save to (default: "preload_data.bin")
	*/
	static void save(const SmartArray<T>& ob, std::string source = FILENAME);

	/**
	* @brief Load a SmartArray from a binary file.
	*
	* Clears the current array and fills it with data from the file.
	*
	* @param ob SmartArray object to load data into
	* @param source Filename to load from (default: "preload_data.bin")
	*/
	static void load(SmartArray<T>& ob, std::string source = FILENAME);
};

template <typename T>
std::filesystem::path SmartArrayIO<T>::GetFileDirectory(std::string filename) {
	std::filesystem::path exeDir = GetExeDirectory();
	std::filesystem::path filePath = exeDir / ".." / "app" / "files" / filename;
	filePath = std::filesystem::weakly_canonical(filePath);

	return filePath;
}

template <typename T>
void SmartArrayIO<T>::save(const SmartArray<T>& ob, std::string source) {
	std::fstream file;
	file.open(GetFileDirectory(source), std::ios::out | std::ios::binary);

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
void SmartArrayIO<T>::load(SmartArray<T>& ob, std::string source) {
	std::fstream file;
	file.open(GetFileDirectory(source), std::ios::in | std::ios::binary);

	if (!file.is_open()) {
		std::cerr << "Could not open file at directory: " << GetFileDirectory(source) << "\n";
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
