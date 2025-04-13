cmake_minimum_required(VERSION 3.8)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)

add_executable(yagbe_tests
    main.cpp
    src/decompiler_tests.cpp
    src/emulator_tests.cpp
)
target_include_directories(yagbe_tests PRIVATE ${YAGBE_LIB_HEADERS_DIR})
target_link_libraries(yagbe_tests PRIVATE yagbe-lib gtest)
add_custom_command(TARGET yagbe_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/resources/ROMs/Tetris.gb ${CMAKE_CURRENT_BINARY_DIR}/Tetris.gb
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Copy Tetris.gb"
)
