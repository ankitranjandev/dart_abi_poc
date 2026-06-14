cmake_minimum_required(VERSION 3.10)
project(dart_abi_poc CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dynamically locate the Dart SDK include directory via your environment
if(NOT DEFINED DART_SDK_PATH)
    message(STATUS "DART_SDK_PATH not set. Defaulting to local dart_headers folder.")
    set(DART_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dart_headers")
else()
    set(DART_SDK_PATH "${DART_SDK_PATH}/include")
endif()

include_directories(${DART_SDK_PATH})

# Define your compiled extension output
add_library(dart_abi_extension SHARED src/my_extension.cpp)
