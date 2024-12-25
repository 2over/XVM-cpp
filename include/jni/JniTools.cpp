//
// Created by ziya on 2024/12/16.
//

#include "JniTools.h"

extern JNIEnv *g_env;

const char *JniTools::getCharsFromJString(JNIEnv *env, jstring str, jboolean is_copy) {
    return const_cast<char *>(env->GetStringUTFChars(str, &is_copy));
}

string *JniTools::jstringToString(JNIEnv *env, jstring str, jboolean is_copy) {
    const char *s = getCharsFromJString(env, str, is_copy);

    return new string(s);
}

jstring JniTools::stringToJString(JNIEnv *env, const string &str) {
    return NULL;
}

jfieldID JniTools::getStaticField(const string &class_name, const string &field_name, const string &descriptor_name) {
    jclass system_class = g_env->FindClass(class_name.c_str());
    if (NULL == system_class) {
        INFO_PRINT("不村存在的类: %s\n", class_name.c_str());
        exit(-1);
    }

    jfieldID field = g_env->GetStaticFieldID(system_class, field_name.c_str(), descriptor_name.c_str());
    if (NULL == field) {
        INFO_PRINT("%s 中不存在属性: %s\n", class_name.c_str(), field_name.c_str());
        exit(-1);
    }

    return field;
}

jobject
JniTools::getStaticObjectField(const string &class_name, const string &field_name, const string &descriptor_name) {
    jclass system_class = g_env->FindClass(class_name.c_str());
    if (NULL == system_class) {
        INFO_PRINT("不存在的类: %s\n", class_name.c_str());
        exit(-1);
    }

    jfieldID field = g_env->GetStaticFieldID(system_class, field_name.c_str(), descriptor_name.c_str());
    if (NULL == field) {
        INFO_PRINT("%s 中不存在属性:  %s\n", class_name.c_str(), field_name.c_str());
        exit(-1);
    }

    return g_env->GetStaticObjectField(system_class, field);
}

jobject JniTools::stringToJavaString(const string &s) {
    jclass string_class = g_env->FindClass("java/lang/String");
    jmethodID construct = g_env->GetMethodID(string_class, "<init>", "([B)V");

    jbyteArray array = g_env->NewByteArray(s.size());
    g_env->SetByteArrayRegion(array, 0, s.size(), reinterpret_cast<const jbyte *>(s.c_str()));

    return g_env->NewObject(string_class, construct, array);
}

jmethodID JniTools::getMethod(const string &class_name, const string &method_name, const string &descriptor_name) {
    jclass system_class = g_env->FindClass(class_name.c_str());

    if (NULL == system_class) {
        INFO_PRINT("不存在的类: %s\n", class_name.c_str());
        exit(-1);
    }

    jmethodID method = g_env->GetMethodID(system_class, method_name.c_str(), descriptor_name.c_str());
    if (NULL == method) {
        INFO_PRINT("%s 中不存在方法: %s\n", class_name.c_str(), method_name.c_str());
        exit(-1);
    }

    return method;
}

jobject JniTools::createJavaLong(jlong l) {
    jclass clazz = g_env->FindClass("java/lang/Long");
    if (NULL == clazz) {
        INFO_PRINT("不存在的类: java/lang/Long\n");
        exit(-1);
    }

    jmethodID construct = g_env->GetMethodID(clazz, "<init>", "(J)V");
    if (NULL == construct) {
        INFO_PRINT("java/lang/Long中不存在方法:  <init>\n");
        exit(-1);
    }

    return g_env->NewObject(clazz, construct, l);
}

jlong JniTools::javaLongToLong(jobject obj) {
    jclass clazz = g_env->FindClass("java/lang/Long");
    if (NULL == clazz) {
        INFO_PRINT("不存在的类: java/long/Long\n");
        exit(-1);
    }
    jmethodID method = g_env->GetMethodID(clazz, "longValue", "()J");
    if (NULL == method) {
        INFO_PRINT("java/lang/Long 中不存在方法: longValue\n");
        exit(-1);
    }

    return g_env->CallLongMethod(obj, method);
}

