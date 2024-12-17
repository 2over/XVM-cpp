//
// Created by ziya on 2024/12/16.
//

#ifndef XVM_CPP_JNITOOLS_H
#define XVM_CPP_JNITOOLS_H

#include "../common.h"
#include "jni.h"


class JniTools {
    // 字符串处理
public:
    static const char *getCharsFromJString(JNIEnv *env, jstring str, jboolean is_copy);

    static string *jstringToString(JNIEnv *env, jstring str, jboolean is_copy);

    static jstring stringToJString(JNIEnv *env, const string &str);

    static jobject stringToJavaString(const string &s);

public:
    static jfieldID getStaticField(const string &class_name, const string &field_name, const string &descriptor_name);

    static jobject
    getStaticObjectField(const string &class_name, const string &field_name, const string &descriptor_name);

    static jmethodID getMethod(const string &class_name, const string &method_name, const string &descriptor_name);

public:
    static jobject createJavaLong(jlong l);

    static jlong javaLongToLong(jobject obj);

public:
    static string &replaceAll(string &str, const string &old_value, const string &new_value) {
        while (true) {
            string::size_type pos(0);

            if ((pos = str.find(old_value)) != string::npos) {
                str.replace(pos, old_value.length(), new_value);
            } else {
                break;
            }
        }

        return str;
    }

};


#endif //XVM_CPP_JNITOOLS_H
