cmake_minimum_required(VERSION 3.10)

# Project name
project(Store)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(store 
    main.cpp
    lib/Store/store.cpp
)