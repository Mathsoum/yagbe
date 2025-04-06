cmake_minimum_required(VERSION 3.8)

project(yagbe CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -O3")

set(YAGBE_LIB_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/yagbe-lib)

add_subdirectory(src)
add_subdirectory(test)

