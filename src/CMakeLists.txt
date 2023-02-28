cmake_minimum_required(VERSION 3.22)
project(Vector)

set(CMAKE_CXX_STANDARD 20)

add_executable(Archiver
        archiver.cpp
        parser.cpp
        bit_num.cpp
        build_canonical_haffman.cpp
        compress_algoritm.cpp compressor.cpp
        decompressor.cpp
        file_reader.cpp
        file_writer.cpp
        trie.cpp)
