cmake_minimum_required(VERSION 3.16)

project(Num VERSION 1.0.0 LANGUAGES CXX)

add_library(Num INTERFACE)
add_library(Num::Num ALIAS Num)

target_compile_features(Num INTERFACE cxx_std_11)
target_include_directories(Num INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    add_executable(num_basic examples/basic.cpp)
    target_link_libraries(num_basic PRIVATE Num::Num)
endif()
