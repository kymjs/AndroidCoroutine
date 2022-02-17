#include <jni.h>
#include <string>
#include <map>
#include "CoroutineDespatcher.h"
#include "OSThread.h"
#include "OSCoroutine.h"
#include "log.h"
#include "ConcurrenceQueue.h"

#ifdef __cplusplus
extern "C" {
#endif
static std::map<jint, OSThread *> threads;

JNIEXPORT void JNICALL
Java_com_kymjs_thread_LiteThread_startNative(JNIEnv *env, jobject thiz) {
}

JNIEXPORT void JNICALL
Java_com_kymjs_thread_LiteThread_yield(JNIEnv *env, jobject thiz) {
    LOGD("calling yield operation");
    sched_yield();
}

JNIEXPORT void JNICALL
Java_com_kymjs_thread_LiteThread_sleep(JNIEnv *env, jclass clazz, jlong millis, jint thread_id) {
}

JNIEXPORT jboolean JNICALL
Java_com_kymjs_thread_LiteThread_isInterrupt(JNIEnv *env, jobject thiz) {
    LOGD("getting intterrupt flag");
    return 0;
}

JNIEXPORT void JNICALL
Java_com_kymjs_thread_LiteThread_interrupt(JNIEnv *env, jobject thiz) {
    LOGD("getting intterrupt flag");
}

JNIEXPORT void JNICALL
Java_com_kymjs_thread_LiteThread_resume(JNIEnv *env, jobject thiz) {
    LOGD("getting intterrupt flag");
}

JNIEXPORT void JNICALL
Java_com_kymjs_coroutine_Coroutine_init(JNIEnv *env, jobject thiz, jlong jThreadId) {
    auto *pThread = threads.find(jThreadId)->second;
    if (pThread == nullptr) {
        pThread = new OSThread(env, jThreadId);
        pThread->start();
        threads.insert(std::map<jint, OSThread *>::value_type(pThread->threadId, pThread));
    }
}

JNIEXPORT void JNICALL
Java_com_kymjs_coroutine_Coroutine_async(JNIEnv *env, jobject thiz) {
    jclass jCroutineClass = env->GetObjectClass(thiz);
    jfieldID jThreadId = env->GetFieldID(jCroutineClass, "threadId", "J");
    jlong threadId = env->GetLongField(thiz, jThreadId);
    threads.find(threadId)->second->despatcher->attachCoroutine(thiz);
}

JNIEXPORT void JNICALL
Java_com_kymjs_coroutine_Coroutine_delay(JNIEnv *env, jobject thiz, jlong millis) {
}

JNIEXPORT void JNICALL
Java_com_kymjs_coroutine_Coroutine_join(JNIEnv *env, jobject thiz) {
    jclass jCroutineClass = env->GetObjectClass(thiz);
    jfieldID jThreadId = env->GetFieldID(jCroutineClass, "threadId", "J");
    jlong threadId = env->GetLongField(thiz, jThreadId);
    threads.find(threadId)->second->despatcher->join(thiz);
}

#ifdef __cplusplus
}
#endif
