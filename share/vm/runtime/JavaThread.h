//
// Created by xiehao on 2024/12/19.
//

#ifndef XVM_CPP_JAVATHREAD_H
#define XVM_CPP_JAVATHREAD_H

#include "VirtualFrame.h"

class OSThread;
class JavaThread {
private:
    stack<VirtualFrame*> _frames;

    jobject _oop;
    OSThread* _osthread;
    jobject _run_oop;
public:
    JavaThread() {}
    JavaThread(jobject o);

    stack<VirtualFrame *>& frames() {
        return _frames;
    }

public:
    void set_osthread(OSThread* osthread) {
        _osthread = osthread;
    }

    void set_run_oop(jobject oop) {
        _run_oop = oop;
    }

    jobject get_run_oop() {
        return _run_oop;
    }
public:
    void run();
};


#endif //XVM_CPP_JAVATHREAD_H
