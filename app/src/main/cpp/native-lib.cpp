#include <jni.h>
#include <string>
#include <map>
#include "CoroutineThread.h"
#include "OSThread.h"
#include "log.h"

#ifdef __cplusplus
extern "C" {
#endif
map<jint, CoroutineThread *> threads;

JNIEXPORT void JNICALL
Java_com_kymjs_thread_LiteThread_startNative(JNIEnv *env, jobject thiz) {
    CoroutineThread *pLiteThread = new CoroutineThread(env, thiz);
    jclass cls = env->GetObjectClass(pLiteThread->jThreadObjectRef);
    jfieldID jfieldId = env->GetFieldID(cls, "threadId", "I");
    jint threadId = env->GetIntField(pLiteThread->jThreadObjectRef, jfieldId);
    threads.insert(map<jint, CoroutineThread *>::value_type(threadId, pLiteThread));
    LOGD("threadId=%d", threadId);
    OSThread osThread(pLiteThread);
    osThread.start();
}

JNIEXPORT void JNICALL
Java_com_kymjs_thread_LiteThread_yield(JNIEnv *env, jobject thiz) {
    LOGD("calling yield operation");
    sched_yield();
}

JNIEXPORT void JNICALL
Java_com_kymjs_thread_LiteThread_sleep(JNIEnv *env, jclass clazz, jlong millis, jint thread_id) {
    if (millis == 0) {
        sched_yield();
    } else {
        if (thread_id == 0) {
            // 主线程
            Suspender parker;
            parker.park(millis);
            return;
        }
        CoroutineThread *pLiteThread = threads.find(thread_id)->second;
        pLiteThread->parker.park(millis);
    }
}

JNIEXPORT jboolean JNICALL
Java_com_kymjs_thread_LiteThread_isInterrupt(JNIEnv *env, jobject thiz) {
    LOGD("getting intterrupt flag");
    jclass cls = env->GetObjectClass(thiz);
    jfieldID jfieldId = env->GetFieldID(cls, "threadId", "I");
    jint threadId = env->GetIntField(thiz, jfieldId);
    CoroutineThread *pLiteThread = threads.find(threadId)->second;
    return pLiteThread->interruptState;
}

JNIEXPORT void JNICALL
Java_com_kymjs_thread_LiteThread_interrupt(JNIEnv *env, jobject thiz) {
    LOGD("getting intterrupt flag");
    jclass cls = env->GetObjectClass(thiz);
    jfieldID jfieldId = env->GetFieldID(cls, "threadId", "I");
    jint threadId = env->GetIntField(thiz, jfieldId);
    CoroutineThread *pLiteThread = threads.find(threadId)->second;
    pLiteThread->interruptState = true;
    pLiteThread->parker.unpark();
}

JNIEXPORT void JNICALL
Java_com_kymjs_thread_LiteThread_resume(JNIEnv *env, jobject thiz) {
    LOGD("getting intterrupt flag");
    jclass cls = env->GetObjectClass(thiz);
    jfieldID jfieldId = env->GetFieldID(cls, "threadId", "I");
    jint threadId = env->GetIntField(thiz, jfieldId);
    CoroutineThread *pLiteThread = threads.find(threadId)->second;
    pLiteThread->interruptState = false;
    pLiteThread->parker.park(5000);
}

JNIEXPORT void JNICALL
Java_com_kymjs_coroutine_Coroutine_async(JNIEnv *env, jobject thiz) {

}

JNIEXPORT jobject JNICALL
Java_com_kymjs_coroutine_Coroutine_await(JNIEnv *env, jobject thiz) {
}

JNIEXPORT void JNICALL
Java_com_kymjs_coroutine_Coroutine_delay(JNIEnv *env, jobject thiz, jlong millis) {
}

#ifdef __cplusplus
}
#endif

