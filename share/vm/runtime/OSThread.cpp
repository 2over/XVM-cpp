//
// Created by xiehao on 2024/12/19.
//

#include "OSThread.h"
#include "JavaThread.h"

extern JavaVM* g_jvm;
extern JNIEnv* g_env;

pthread_mutex_t lock;
void* run_java_run(void* arg) {
    OSThread* thread = static_cast<OSThread*>(arg);

    JNIEnv *env = NULL;
    g_jvm->AttachCurrentThread((void**)&env, NULL);

    // 等待创建线程工作完成才执行
    pthread_mutex_lock(&lock);
    WRITE("子线程已进入阻塞等待\n");

    // 执行run 方法
    jclass cl = env->GetObjectClass(thread->get_javathread()->get_run_oop());
    if (NULL == cl) {
        INFO_PRINT("GetObjectClass fail\n");
        exit(-1);
    }

    jmethodID run = env->GetMethodID(cl, "run", "()V");
    if (NULL == run) {
        INFO_PRINT("GetMethodID fail\n");
        exit(-1);
    }

    env->CallVoidMethod(thread->get_javathread()->get_run_oop(), run);

    // detach thread
    g_jvm->DetachCurrentThread();
}

OSThread::OSThread(JavaThread *thread) {
    _javathread = thread;
    int status = pthread_mutex_init(_start_thread_lock, NULL);

    ASSERT_ZERO(status, "pthread_mutex_init fail\n");

    status = pthread_cond_init(_start_thread_cond, NULL);

    // 设置线程分离属性
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&_tid, &thread_attr, run_java_run, this);
    pthread_attr_destroy(&thread_attr);
}