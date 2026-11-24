
cmake_minimum_required(VERSION 4.0)
project(oop_lab1_trie)

set(CMAKE_CXX_STANDARD 20)

add_executable(oop_lab1_trie
        main.cpp
        Trie.cpp
)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(trie_tests
        Trie_test.cpp
        Trie.cpp
)

target_link_libraries(trie_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(trie_tests)

