# Setup
cmake_minimum_required(VERSION 3.15)
project(simpleicp)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wshadow -Wpedantic -fsanitize=undefined,address")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Find Packages
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(cxxopts CONFIG REQUIRED)
find_package(nanoflann CONFIG REQUIRED)

# Create ICP library
add_library(simpleicp_lib
    src/simpleicp.cpp
    src/pointcloud.cpp
    src/corrpts.cpp)

# Link libraries 
target_link_libraries(simpleicp_lib PUBLIC Eigen3::Eigen cxxopts::cxxopts nanoflann::nanoflann)
target_include_directories(simpleicp_lib PUBLIC src include)

# Create executable
add_executable(simpleicp src/simpleicp-cli.cpp)
target_link_libraries(simpleicp PRIVATE simpleicp_lib)