cmake_minimum_required(VERSION 3.8)

add_subdirectory(yagbe-lib)

add_executable(yagbe main.cpp)
target_include_directories(yagbe PRIVATE ${YAGBE_LIB_HEADERS_DIR})
target_link_libraries(yagbe PRIVATE yagbe-lib)