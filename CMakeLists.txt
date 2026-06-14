cmake_minimum_required(VERSION 3.10)
project(dart_abi_poc C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force DWARF debug generation for libabigail
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g -O0)

# Try to find Dart SDK headers
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../sdk/runtime/include")
    set(DART_SDK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../sdk/runtime/include")
    set(DART_API_DL_C "${DART_SDK_INCLUDE_DIR}/dart_api_dl.c")
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dart_headers")
    set(DART_SDK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dart_headers")
    # In CI, we download dart_api_dl.c to dart_headers
    set(DART_API_DL_C "${DART_SDK_INCLUDE_DIR}/dart_api_dl.c")
endif()

if(NOT DART_SDK_INCLUDE_DIR)
    message(FATAL_ERROR "Dart SDK headers not found! Please ensure ../sdk exists or dart_headers contains the headers.")
endif()

include_directories(${DART_SDK_INCLUDE_DIR})

# Check if dart_api_dl.c exists
if(NOT EXISTS "${DART_API_DL_C}")
    message(WARNING "dart_api_dl.c not found at ${DART_API_DL_C}. Linking might fail.")
endif()

add_library(dart_abi_extension SHARED 
    src/sample_extension.cpp 
    ${DART_API_DL_C}
)
