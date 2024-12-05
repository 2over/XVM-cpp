cmake_minimum_required(VERSION 3.16.5)
project(XVM_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_CXX_STANDARD 17)
include_directories("/home/ziya/Documents/openjdk/build/linux-x86_64-normal-server-slowdebug/jdk/include/")
include_directories("/home/ziya/Documents/openjdk/build/linux-x86_64-normal-server-slowdebug/jdk/include/linux")

add_executable(XVM_cpp main.cpp include/common.h include/gc/interface/garbage_collect.h include/gc/gc_factory.h include/memory/memory_cell.h include/memory/memory_chunk.h include/memory/memory_pool.h include/gc/mark_clean.h include/gc/mark_compact.h include/gc/mark_copy.h include/jni/Handle.cpp include/jni/Handle.h share/vm/oops/Klass.cpp share/vm/oops/Klass.h share/vm/oops/MethodInfo.cpp share/vm/oops/MethodInfo.h src/memory/memory_cell.cpp src/memory/memory_chunk.cpp src/memory/memory_pool.cpp src/gc/gc_factory.cpp src/gc/mark_clean.cpp src/gc/mark_compact.cpp src/gc/mark_copy.cpp)
