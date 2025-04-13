cmake_minimum_required(VERSION 3.8)
project(yagbe-lib CXX)

set(SOURCE_FILES
    decompiler.h
    decompiler.cpp
    emulator.h
    emulator.cpp
)

add_library(yagbe-lib SHARED STATIC ${SOURCE_FILES})
