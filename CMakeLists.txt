cmake_minimum_required(VERSION 3.1)

project(Ulti)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "-O0 -g ${CXX11_FLAG} -Werror -Wall -fno-inline")
else()
    set(CMAKE_CXX_FLAGS "-O3 -g ${CXX11_FLAG} -Werror -Wall -DNDEBUG")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ulti_core)

add_subdirectory(core)
add_subdirectory(client)
add_subdirectory(server)
