//
// Created by xiehao on 2024/12/19.
//

#include "JavaThread.h"
#include "OSThread.h"

void JavaThread::run() {

    sleep(3);

    pthread_cond_signal(_osthread->_start_thread_cond);
}

JavaThread::JavaThread(jobject o) {
    _oop = o;
    _osthread = new OSThread(this);
}