//
// Created by ziya on 2024/12/19.
//

#include "BytecodeInterpreter.h"
#include "../oops/InstanceKlass.h"
#include "../oops/CodeAttribute.h"
#include "jni.h"
#include "../../../include/jni/JniTools.h"


extern JNIEnv* g_env;
void BytecodeInterpreter::run(JavaThread *thread, MethodInfo *method) {

    InstanceKlass* klass = static_cast<InstanceKlass *>(method->klass());
    CodeAttribute* code_attribute = static_cast<CodeAttribute *> (method->attribute());
    CodeStream* code_stream = code_attribute->codes();
    VirtualFrame* frame = thread->frames().top();

    unsigned char c;
    while (!code_stream->end()) {
        c = code_stream->get_u1();

        switch (c) {
            case _getstatic: {
                INFO_PRINT("执行指令: _getstatic\n");

                int operand = code_stream->get_u2();
                int i = klass->constant_pool()->get_item_int(operand);
                string class_name = klass->constant_pool()->get_class_name_from_fieldref(i);
                string field_name = klass->constant_pool()->get_field_name_from_fieldref(i);
                string descriptor_name = klass->constant_pool()->get_field_descriptor_from_fieldref(i);

                jobject field_val = JniTools::getStaticObjectField(class_name.c_str(),
                        field_name.c_str(), descriptor_name.c_str());

                frame->operand_stack().push(new StackValue(T_OBJECT, field_val));
                break;
            }
            case _getfield: {
                INFO_PRINT("执行指令: _getfield\n");
                short operand = code_stream->get_u2();
                int index = klass->constant_pool()->get_item_int(operand);

                string class_name = klass->constant_pool()->get_class_name_from_fieldref(index);
                string field_name = klass->constant_pool()->get_field_name_from_fieldref(index);

                // 获取栈桢中的参数
                instanceOop  oop = reinterpret_cast<instanceOop>(frame->operand_stack().top()->data());
                frame->operand_stack().pop();

                // 取出数据
                long val = oop->find(class_name, field_name);

                // 压入栈
                frame->operand_stack().push(new StackValue(T_INT, val));

                break;
            }
    }
}