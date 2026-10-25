cmake_minimum_required(VERSION 3.16)
project(oop_lab0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_CLANG_TIDY
        "C:/Program Files/LLVM/bin/clang-tidy.exe"
        "--extra-arg-before=--target=x86_64-w64-mingw32"
        "--extra-arg-before=--sysroot=C:/Program Files/JetBrains/CLion 2025.2.1/bin/mingw"
)

add_executable(oop_lab0 main.cpp
        word_counter.cpp
        word_counter.h
        text_reader.cpp
        text_reader.h
        csv_writer.cpp
        csv_writer.h)
