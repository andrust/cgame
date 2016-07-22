cmake_minimum_required(VERSION 3.1)

project(Ulti)

enable_testing()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "-O0 -g --std=c++11 -Werror -Wall -fno-inline")
else()
    set(CMAKE_CXX_FLAGS "-O3 -g --std=c++11 -Werror -Wall -DNDEBUG")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ulti_core)

add_subdirectory(core)
add_subdirectory(client)
add_subdirectory(server)
