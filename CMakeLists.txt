cmake_minimum_required(VERSION 3.16)
project(oop_lab0)

set(CMAKE_CXX_STANDARD 20)

find_program(CLANG_TIDY clang-tidy)

if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

add_executable(oop_lab0 main.cpp
        word_counter.cpp
        word_counter.h
        text_reader.cpp
        text_reader.h
        csv_writer.cpp
        csv_writer.h)
