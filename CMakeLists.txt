cmake_minimum_required(VERSION 3.10)
project(microCBOR)

set(BINARY ${CMAKE_PROJECT_NAME}_lib)

option(BUILD_TESTS "Build test programs" OFF)

include_directories(include)

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)