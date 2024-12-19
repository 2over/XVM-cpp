//
// Created by xiehao on 2024/12/19.
//

#ifndef XVM_CPP_OSTHREAD_H
#define XVM_CPP_OSTHREAD_H
#include "../../../include/common.h"
class JavaThread;

class OSThread {
public:
    JavaThread* _javathread;
    pthread_mutex_t     _start_thread_lock[1];
    pthread_cond_t      _start_thread_cond[1];

    pthread_t           _tid;

public:
    OSThread(JavaThread* thread);

    JavaThread* get_javathread() {
        return _javathread;
    }
};


#endif //XVM_CPP_OSTHREAD_H
