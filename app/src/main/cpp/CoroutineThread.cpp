//
// Created by zhangtao on 2022/2/11.
//

#include "CoroutineThread.h"

CoroutineThread::CoroutineThread(JNIEnv *env, jobject jobj) {
    env->GetJavaVM(&(this->jvm));
    this->jThreadObjectRef = env->NewGlobalRef(jobj);
}

CoroutineThread::~CoroutineThread() {
    jvm->DetachCurrentThread();
}

void CoroutineThread::run() {
    JNIEnv *env;
    if (jvm->AttachCurrentThread(&env, NULL) != 0) {
        LOGD("Faile to attach");
    }

    jclass cls = env->GetObjectClass(jThreadObjectRef);
    jmethodID runId = env->GetMethodID(cls, "run", "()V");
    if (runId != nullptr) {
        env->CallVoidMethod(jThreadObjectRef, runId);
    } else {
        LOGD("No run method found in CoroutineThread!!");
    }
    env->DeleteGlobalRef(jThreadObjectRef);
}

