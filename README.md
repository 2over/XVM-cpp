first commit

## 生成头文件
```bash
1. 进入到该目录 /home/ziya/IdeaProjects/XVM/src/main/java
2.javac com/cover/jvm/jdk/classes/Handle.java
3.javac -h  /home/ziya/IdeaProjects/XVM/jni  com/cover/jvm/jdk/classes/JniEnv.java

```


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
