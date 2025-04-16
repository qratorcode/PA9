cmake_minimum_required(VERSION 3.30)
project(PA9)

# Set C++ standard (e.g., C++14 or C++17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(PA9 main.cpp)

# --- Find OpenCV ---
# Provide the specific path to the OpenCV CMake configuration directory
# Make sure this path matches exactly where Homebrew installed it
set(OpenCV_DIR /usr/local/Cellar/opencv/4.11.0_1/)

# Find and link OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(PA9 ${OpenCV_LIBS})