//
// Created by ziya on 2024/12/19.
//

#ifndef XVM_CPP_BYTECODEINTERPRETER_H
#define XVM_CPP_BYTECODEINTERPRETER_H


#include "../runtime/JavaThread.h"
#include "../oops/MethodInfo.h"

class BytecodeInterpreter {

public:
    static void run(JavaThread* thread, MethodInfo * methodInfo);

};


#endif //XVM_CPP_BYTECODEINTERPRETER_H
