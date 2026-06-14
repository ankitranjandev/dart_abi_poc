cmake_minimum_required(VERSION 3.10)
project(dart_abi_poc CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force DWARF debug generation for libabigail
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g -O0)

# Reference the SDK include folder located in the parent directory
set(DART_SDK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../sdk/runtime/include")
include_directories(${DART_SDK_INCLUDE_DIR})

# Compile your logic AND Dart's dynamic linking implementation straight from the SDK repo
add_library(dart_abi_extension SHARED 
    src/my_extension.cpp 
    ../sdk/runtime/include/dart_api_dl.c
)
