#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

typedef void *              pvoid;
typedef unsigned char       byte;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;

typedef union {
    long        l_dummy;
    double      d_dummy;
    void *      p_dummy;
}Align;

#define ALIGN_SIZE          (sizeof(Align))

typedef enum {
    GC_MARK_CLEAN,
    GC_MARK_COLLECT,
    GC_MARK_COPY,
    GC_G1,
}GC_Type;

#define UseParallelGC false
#define UseG1GC false
#define UseSerialGC false
#define UseConcMarkSweepGC false
#define UseAdaptiveSizePolicy false

#define DEFAULT_GC_TYPE GC_MARK_CLEAN

#define UseBiasedLocking false
#define UseCompressedClassPointers false

typedef class objArrayOopDesc* objArrayOop;

// Analogous opaque struct for metdata allocated from metaspaces;
class MetaWord {
private:
    char* i;
};

/*=================================
 *  自定义打印输出
 ==================================*/
#define INFO_OUTPUT         3
#define WARNING_OUTPUT      2
#define DEBUG_OUTPUT        1
#define ERROR_OUTPUT        0

#define DEBUG
#define DEBUG_LEVEL         INFO_OUTPUT

#define PRINT(info, ...) do{ \
    printf("[Info] (%s:%d->%s):" info"", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
}while(0)

#define INFO_PRINT(info, ...) do{ \
    if(DEBUG_LEVEL>=INFO_OUTPUT){ \
        printf("[Info] (%s:%d->%s):" info"", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
    } \
}while(0)

#define WARNING_PRINT(info, ...) do{ \
    if(DEBUG_LEVEL>=WARNING_OUTPUT){ \
        printf("[Warning] (%s:%d->%s):" info"", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
    } \
}while(0)

#define DEBUG_PRINT(info,...) do{ \
    if(DEBUG_LEVEL>=DEBUG_OUTPUT){ \
        printf("[Debug] (%s:%d->%s):" info"",__FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__); \
    } \
}while(0)

#define ERROR_PRINT(info, ...) do{ if(DEBUG_LEVEL>=ERROR_OUTPUT){ printf("[Error] (%s:%d->%s):" info"", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); } }while(0)
#define assert(cond, msg) { if (!(cond))  {fprintf(stderr, "assert fail %s %d: %s\n", __FILE__, __LINE__, msg); abort(); }}

#define WRITE(str) do {\
    write(STDOUT_FILENO, str, strlen(str)); \
} while(0)

#define ASSERT_ZERO(status, str) do {\
    if (0 != status) {\
        WRITE(str); \
        exit(-1); \
    } \
} while(0)


