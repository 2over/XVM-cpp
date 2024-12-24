//
// Created by xiehao on 2024/12/19.
//

#include "JavaNativeInterface.h"
#include "../runtime/JavaThread.h"
#include "../runtime/Threads.h"
#include "../oops/CodeAttribute.h"
#include "../interpreter/BytecodeInterpreter.h"

MethodInfo *JavaNativeInterface::getMethodID(InstanceKlass *klass, string method_name, string descriptor_name) {
    vector<MethodInfo *> methods = klass->methods();
    MethodInfo *ret = NULL;

    for (int i = 0; i < methods.size(); ++i) {
        MethodInfo *tmp = methods[i];

        if ((tmp->name() == method_name) && (tmp->descriptor() == descriptor_name)) {
            ret = tmp;
        }
    }

    return ret;
}

MethodInfo *JavaNativeInterface::getVMethodID(InstanceKlass *klass, string method_name, string descriptor_name) {
    vector<MethodInfo *> methods = klass->vtable();
    MethodInfo *ret = NULL;

    for (int i = 0; i < methods.size(); ++i) {
        MethodInfo *tmp = methods[i];

        if ((tmp->name() == method_name) && (tmp->descriptor() == descriptor_name)) {
            ret = tmp;
        }
    }

    return ret;
}

void JavaNativeInterface::callStaticVoidMethod(InstanceKlass *klass, MethodInfo *method, ...) {
    JavaThread *thread = Threads::current_thread();
    CodeAttribute *attribute = static_cast<CodeAttribute *>(method->attribute());

    // 创建线程栈
    VirtualFrame *frame = new VirtualFrame(attribute->max_locals());

    // 线程与栈帮顶
    thread->frames().push(frame);

    BytecodeInterpreter::run(thread, method);
    INFO_PRINT("结束\n");
}

void JavaNativeInterface::callVoidMethod(InstanceKlass *klass, MethodInfo *method, ...) {
    JavaThread *thread = Threads::current_thread();
    CodeAttribute *attribute = static_cast<CodeAttribute *>(method->attribute());

    // 取得上个方法的栈桢
    VirtualFrame *frame = thread->frames().top();

    // 取得this指针
    StackValue *value = frame->operand_stack().top();

    // 创建运行 该方法的栈桢
    VirtualFrame *current_frame = new VirtualFrame(attribute->max_locals());

    thread->frames().push(current_frame);

    INFO_PRINT("栈桢数量: %d\n", thread->frames().size());

    // 给this指针赋值
    current_frame->local_variable_table()[0] = value;

    BytecodeInterpreter::run(thread, method);

    INFO_PRINT("结束\n");

}