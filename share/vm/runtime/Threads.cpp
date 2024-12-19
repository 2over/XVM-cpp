//
// Created by ziya on 2024/12/19.
//

#include "Threads.h"
JavaThread* Threads::_current_thread = NULL;

JavaThread *Threads::current_thread() {
    return _current_thread;
}

void Threads::set_current_thread(JavaThread *thread) {
    _current_thread = thread;
}


