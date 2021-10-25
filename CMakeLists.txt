cmake_minimum_required(VERSION 3.10)
project(CBOR)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
