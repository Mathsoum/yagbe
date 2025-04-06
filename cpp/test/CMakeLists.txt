cmake_minimum_required(VERSION 3.8)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)

add_executable(yagbe_tests 
    main.cpp
    src/decompiler_tests.cpp
)
target_include_directories(yagbe_tests PRIVATE ${YAGBE_LIB_HEADERS_DIR})
target_link_libraries(yagbe_tests PRIVATE yagbe-lib gtest)