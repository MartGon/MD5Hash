# Specify the minimum version for CMake

cmake_minimum_required(VERSION 3.7)

# Set c++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Remove error
SET(GCC_COVERAGE_COMPILE_FLAGS "-fpermissive")

# Project's name
project(SinfLab)

# Adding finding modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Find OpenCV
#find_package(OpenCV REQUIRED)

# Directories to be included
include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

# Add src directory
add_subdirectory(src)