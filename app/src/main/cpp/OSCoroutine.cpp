//
// Created by zhangtao on 2022/2/14.
//

#include "OSCoroutine.h"

OSCoroutine::OSCoroutine(JNIEnv *env, jobject jobj) {
    env->GetJavaVM(&(this->jvm));
    this->jCoroutine = env->NewGlobalRef(jobj);
    jclass jCoroutineClass = env->GetObjectClass(jCoroutine);
    jfieldID jCoroutineId = env->GetFieldID(jCoroutineClass, "coroutineId", "J");
    this->coroutineId = env->GetLongField(jCoroutine, jCoroutineId);
}

OSCoroutine::~OSCoroutine() {
}

void OSCoroutine::async(JNIEnv *env) {
    if (jvm->AttachCurrentThread(&env, NULL) != 0) {
        LOGD("faile to attach");
    }

    jclass jCoroutineClass = env->GetObjectClass(jCoroutine);
    jmethodID runId = env->GetMethodID(jCoroutineClass, "run", "()Ljava/lang/Object;");
    if (runId != nullptr) {
        await(env, env->CallObjectMethod(jCoroutine, runId));
    } else {
        LOGD("No run method found in Coroutine");
    }
}

void OSCoroutine::await(JNIEnv *env, jobject result) {
    jclass jCoroutineClass = env->GetObjectClass(jCoroutine);
    jmethodID onAwaitMethod = env->GetMethodID(jCoroutineClass, "onAwait", "(Ljava/lang/Object;)V");
    if (onAwaitMethod != nullptr) {
        env->CallVoidMethod(jCoroutine, onAwaitMethod, result);
    }
    env->DeleteGlobalRef(jCoroutine);
}

void OSCoroutine::delay(jlong millis) {

}
