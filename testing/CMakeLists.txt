cmake_minimum_required(VERSION 3.15)
project(icp_test)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wshadow -Wpedantic -fsanitize=undefined,address")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
add_executable(icp_test testing_utils.cpp)
target_link_libraries (icp_test Eigen3::Eigen)