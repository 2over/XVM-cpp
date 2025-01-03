//
// Created by ziya on 2024/12/19.
//

#include "BytecodeInterpreter.h"
#include "../oops/InstanceKlass.h"
#include "../oops/CodeAttribute.h"
#include "jni.h"
#include "../../../include/jni/JniTools.h"
#include "../prims/JavaNativeInterface.h"
#include "../classfile/SystemDictionary.h"


extern JNIEnv *g_env;

void BytecodeInterpreter::run(JavaThread *thread, MethodInfo *method) {

    InstanceKlass *klass = static_cast<InstanceKlass *>(method->klass());
    CodeAttribute *code_attribute = static_cast<CodeAttribute *> (method->attribute());
    CodeStream *code_stream = code_attribute->codes();
    VirtualFrame *frame = thread->frames().top();

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
                instanceOop oop = reinterpret_cast<instanceOop>(frame->operand_stack().top()->data());
                frame->operand_stack().pop();

                // 取出数据
                long val = oop->find(class_name, field_name);

                // 压入栈
                frame->operand_stack().push(new StackValue(T_INT, val));

                break;
            }
            case _putfield: {
                INFO_PRINT("执行指令: _putfield\n");

                short operand = code_stream->get_u2();
                int index = klass->constant_pool()->get_item_int(operand);

                string class_name = klass->constant_pool()->get_class_name_from_fieldref(index);
                string field_name = klass->constant_pool()->get_field_name_from_fieldref(index);

                // 获取栈帧中的参数
                long val = frame->operand_stack().top()->data();
                frame->operand_stack().pop();

                instanceOop oop = reinterpret_cast<instanceOop>(frame->operand_stack().top()->data());
                frame->operand_stack().pop();

                // 保存属性到oop中
                oop->add_field(class_name, field_name, val);

                break;
            }
            case _bipush: {
                INFO_PRINT("执行指令: _bipush\n");
                long v = code_stream->get_u1();

                frame->operand_stack().push(new StackValue(T_INT, v));

                break;
            }
            case _ldc: {
                INFO_PRINT("执行指令: _ldc\n");

                int operand = code_stream->get_u1();
                short index = klass->constant_pool()->get_item_int(operand);

                string *s = klass->constant_pool()->get_item_string2(index);
                frame->operand_stack().push(new StackValue(T_OBJECT, (jlong) s));
                break;
            }
            case _aload_0: {
                INFO_PRINT("执行指令: _aload_0 \n");
                StackValue *value = frame->local_variable_table()[0];
                frame->operand_stack().push(value);
                break;
            }
            case _aload_1: {
                INFO_PRINT("执行指令: _aload_1\n");
                StackValue *value = frame->local_variable_table()[1];
                frame->operand_stack().push(value);
                break;
            }

            case _aload_2: {
                INFO_PRINT("执行指令: _aload_2\n");

                StackValue *value = frame->local_variable_table()[2];
                frame->operand_stack().push(value);
                break;
            }
            case _aload_3: {
                INFO_PRINT("执行指令: _aload_3\n");
                StackValue *value = frame->local_variable_table()[3];
                frame->operand_stack().push(value);
                break;
            }
            case _astore_0: {
                INFO_PRINT("执行指令: _astore_0\n");
                StackValue *value = frame->operand_stack().top();
                frame->operand_stack().pop();

                frame->local_variable_table()[0] = value;
                break;
            }
            case _astore_1: {
                INFO_PRINT("执行指令: _astore_1\n");
                StackValue *value = frame->operand_stack().top();
                frame->operand_stack().pop();

                frame->local_variable_table()[1] = value;
                break;
            }

            case _astore_2: {
                INFO_PRINT("执行指令: _astore_2\n");
                StackValue *value = frame->operand_stack().top();
                frame->operand_stack().pop();

                frame->local_variable_table()[2] = value;
                break;
            }
            case _astore_3: {
                INFO_PRINT("执行指令: _astore_3\n");
                StackValue *value = frame->operand_stack().top();
                frame->operand_stack().pop();

                frame->local_variable_table()[3] = value;
                break;

            }

            case _dup: {
                INFO_PRINT("执行指令: _dup\n");
                StackValue *value = frame->operand_stack().top();

                frame->operand_stack().push(value);

                break;
            }
            case _invokevirtual: {
                INFO_PRINT("执行指令: _invokevirtual\n");
                int operand = code_stream->get_u2();
                int methodref_index = klass->constant_pool()->get_item_int(operand);

                string class_name = klass->constant_pool()->get_class_name_from_methodref(methodref_index);
                string method_name = klass->constant_pool()->get_method_name_from_methodref(methodref_index);
                string descriptor_name = klass->constant_pool()->get_method_descriptor_from_methodref(methodref_index);

                INFO_PRINT("%s, %s, %s\n", class_name.c_str(), method_name.c_str(), descriptor_name.c_str());
                if (0 == class_name.find("java")) {
                    jmethodID method = JniTools::getMethod(class_name.c_str(),
                                                           method_name.c_str(), descriptor_name.c_str());

                    // 取出第一个参数 hello
                    StackValue *value1 = frame->operand_stack().top();
                    frame->operand_stack().pop();

                    // 取出第二个参数 this
                    StackValue *value2 = frame->operand_stack().top();
                    frame->operand_stack().pop();

                    jobject out_object = reinterpret_cast<jobject>(value2->data());

                    if ("(I)V" == descriptor_name) {
                        ERROR_PRINT("%d\n", value1->data());

                        g_env->CallVoidMethod(out_object, method, value1->data());
                    } else {
                        string *s = reinterpret_cast<string *>(value1->data());
                        g_env->CallVoidMethod(out_object, method, JniTools::stringToJavaString(*s));
                    }
                } else {
                    klass->link_class();

                    MethodInfo *methodInfo = JavaNativeInterface::getVMethodID(klass, method_name, descriptor_name);
                    if (NULL == methodInfo) {
                        ERROR_PRINT("%s 中没有找到方法%s, %s\n", class_name.c_str(), method_name.c_str(),
                                    descriptor_name.c_str());
                        exit(-1);
                    }

                    ERROR_PRINT("%s vtable 中找到了分那个法%s, %s\n", class_name.c_str(), method_name.c_str(),
                                descriptor_name.c_str());

                    // 字节码指针重置, 不然重复调用会出现问题
                    CodeAttribute *code_attribute = static_cast<CodeAttribute *>(methodInfo->attribute());
                    code_attribute->codes()->reset();

                    // 调用
                    JavaNativeInterface::callVoidMethod(klass, methodInfo);
                }

                break;
            }
            case _invokespecial: {
                INFO_PRINT("执行指令: _invokespecial\n");

                int operand = code_stream->get_u2();
                int index = klass->constant_pool()->get_item_int(operand);
                string class_name = klass->constant_pool()->get_class_name_from_methodref(index);
                string method_name = klass->constant_pool()->get_method_name_from_methodref(index);
                string descriptor_name = klass->constant_pool()->get_method_descriptor_from_methodref(index);

                if ("java/lang/Object" == class_name) {
                    INFO_PRINT(" 不执行 [ java/lang/Object] 的构造方法\n");
                    break;
                }

                INFO_PRINT("%s, %s, %s\n", class_name.c_str(), method_name.c_str(), descriptor_name.c_str());

                long klass = SystemDictionary::dictionary()->find(class_name);

                // 获取方法信息
                MethodInfo *method = JavaNativeInterface::getMethodID(reinterpret_cast<InstanceKlass *>(klass),
                                                                      method_name, descriptor_name);

                JavaNativeInterface::callVoidMethod(reinterpret_cast<InstanceKlass *>(klass), method);

                break;
            }
            case _new: {
                INFO_PRINT("执行指令: _new\n");
                int operand = code_stream->get_u2();

                int class_index = klass->constant_pool()->get_item_int(operand);
                string class_name = klass->constant_pool()->get_item_string(class_index);

                InstanceKlass *new_klass = static_cast<InstanceKlass *>(SystemDictionary::resolve_or_null(class_name));

                // 加载父类
                SystemDictionary::load_super_class(new_klass);

                long oop = reinterpret_cast<long>(new InstanceOopDesc(new_klass));
                frame->operand_stack().push(new StackValue(T_OBJECT, oop));

                break;
            }
            case _return: {
                INFO_PRINT("执行指令: _return\n");

                thread->frames().pop();

                INFO_PRINT("\t 剩余栈桢: %d\n", thread->frames().size());

                break;
            }
            default: {
                ERROR_PRINT("无法识别的字节码指令: %d\n", c);
                exit(-1);
            }

        }
    }
}