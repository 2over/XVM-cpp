//
// Created by ziya on 2024/12/19.
//

#ifndef XVM_CPP_THREADS_H
#define XVM_CPP_THREADS_H


#include "JavaThread.h"

class Threads {
private:
    static JavaThread* _current_thread;
public:
    static void set_current_thread(JavaThread* thread);
    static JavaThread* current_thread();

};


#endif //XVM_CPP_THREADS_H
