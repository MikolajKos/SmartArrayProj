# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(sa)

add_executable(sa
	app/src/main.cpp
	app/src/SmartArray.cpp
)

target_include_directories(sa PUBLIC ${CMAKE_SOURCE_DIR}/app/includes)