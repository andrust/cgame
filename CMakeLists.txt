cmake_minimum_required(VERSION 2.8)

project(Ulti)

#enable_testing()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "-O0 -g --std=c++11 -Werror -Wall -fno-inline")
else()
    set(CMAKE_CXX_FLAGS "-O3 -g --std=c++11 -Werror -Wall -DNDEBUG")
endif()

#add_subdirectory(/usr/src/gmock ${CMAKE_BINARY_DIR}/gmock)

include_directories(.)

add_subdirectory(core)
add_subdirectory(ulti)
