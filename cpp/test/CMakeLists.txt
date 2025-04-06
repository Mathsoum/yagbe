cmake_minimum_required(VERSION 3.8)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)

set(SOURCE_FILES main.cpp)

add_executable(yagbe_tests main.cpp)
target_link_libraries(yagbe_tests gtest)