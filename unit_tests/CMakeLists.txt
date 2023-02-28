cmake_minimum_required(VERSION 3.22)
project(Vector)

set(CMAKE_CXX_STANDARD 20)

add_executable(archiver_unit_tests
        test_heap.cpp
        test_trie.cpp
        test_bitnum.cpp
        test_write_and_read.cpp
        test_build_canonical_haffman_code.cpp
        ../src/trie.cpp
        ../src/bit_num.cpp
        ../src/file_reader.cpp
        ../src/file_writer.cpp
        ../src/build_canonical_haffman.cpp
        catch/catch_main.cpp)