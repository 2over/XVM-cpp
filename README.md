first commit

# 编译命令
/usr/bin/g++ -shared -fPIC -I/home/ziya/Documents/openjdk/build/linux-x86_64-normal-server-slowdebug/jdk/include 
/home/ziya/Documents/ziya-jvm-teach-cpp/src/jni/com_ziya_jvm_jdk_sun_misc_Unsafe.cpp 
/home/ziya/Documents/ziya-jvm-teach-cpp/src/jni/com_ziya_jvm_jdk_Threads.cpp 
/home/ziya/Documents/ziya-jvm-teach-cpp/src/memory/memory_pool.cpp 
/home/ziya/Documents/ziya-jvm-teach-cpp/src/memory/memory_chunk.cpp 
/home/ziya/Documents/ziya-jvm-teach-cpp/src/memory/memory_cell.cpp 
/home/ziya/Documents/ziya-jvm-teach-cpp/src/gc/gc_factory.cpp 
/home/ziya/Documents/ziya-jvm-teach-cpp/src/gc/mark_clean.cpp   
-o /lib/libjni.so
