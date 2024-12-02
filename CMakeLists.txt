cmake_minimum_required(VERSION 3.16.5)
project(XVM_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(XVM_cpp main.cpp include/common.h include/gc/interface/garbage_collect.h include/gc/gc_factory.h include/memory/memory_cell.h include/memory/memory_chunk.h)
