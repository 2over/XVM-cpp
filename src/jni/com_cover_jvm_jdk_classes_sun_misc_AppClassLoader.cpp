//
// Created by xiehao on 2024/12/25.
//
#include "../../include/jni/com_cover_jvm_jdk_classes_sun_misc_AppClassLoader.h"
#include "../../include/jni/JniTools.h"
#include "../../share/vm/oops/Klass.h"
#include "../../share/vm/classfile/SystemDictionary.h"
#include "../../include/jni/Handle.h"

/*
 * Class:     com_cover_jvm_jdk_classes_sun_misc_AppClassLoader
 * Method:    loadKlass
 * Signature: (Ljava/lang/String;)Lcom/cover/jvm/jdk/classes/Handle;
 */
JNIEXPORT jobject JNICALL Java_com_cover_jvm_jdk_classes_sun_misc_AppClassLoader_loadKlass
        (JNIEnv *env, jclass clazz, jstring className) {
    string *name = JniTools::jstringToString(env, className, true);
    Klass *klass = SystemDictionary::resolve_or_null(*name);

    INFO_PRINT("%s: %p\n", name->c_str(), klass);

    return Handle::klassToHandle(env, klass);

}