# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(sa)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Overriding __cplusplus makro
if (MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

add_executable(sa
	app/src/main.cpp
	app/src/SmartArray.cpp
  "app/src/handlers/ErrorHandler.cpp" "app/src/data/Employee.cpp")

target_include_directories(sa PUBLIC ${CMAKE_SOURCE_DIR}/app/includes)