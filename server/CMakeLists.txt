cmake_minimum_required(VERSION 3.1)

project(Ulti)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "-O0 -g ${CXX11_FLAG} -Werror -Wall -fno-inline")
else()
    set(CMAKE_CXX_FLAGS "-O3 -g ${CXX11_FLAG} -Werror -Wall -DNDEBUG")
endif()

add_library(ulti_core SHARED
    Card.cc
    Card.h
    CardComparison.cc
    CardComparison.h
    CardProperties.h
    Deck.cc
    Deck.h
)

add_executable(ulti_server
    ulti_server.cc
)

target_link_libraries(ulti_server
    ulti_core
)

add_subdirectory(test)
