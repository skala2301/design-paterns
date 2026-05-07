cmake_minimum_required(VERSION 3.12)
project(employee_register)
set(CMAKE_CXX_STANDARD 20)
find_package(libpqxx REQUIRED)

add_library(env_extractor STATIC
    lib/env_extractor.cpp
)
target_include_directories(env_extractor PUBLIC lib)

add_library(model INTERFACE)
target_include_directories(model INTERFACE lib/db)

add_library(employee_model  INTERFACE)
target_include_directories(employee_model INTERFACE src/models)
target_link_libraries(employee_model INTERFACE model)

add_executable(employee_register employee_register.cpp)

target_link_libraries(employee_register PRIVATE
    employee_model 
    env_extractor
    libpqxx::pqxx 
    pq
)