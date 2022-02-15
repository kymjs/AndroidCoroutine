//
// Created by zhangtao on 2022/2/11.
//
#include <jni.h>
#include "Suspender.h"
#include "log.h"

#ifndef COROUTINE_THREAD_H
#define COROUTINE_THREAD_H

using namespace std;

class CoroutineThread {
public:
    JavaVM *jvm;
    jobject jThreadObjectRef;
    Suspender parker;
    bool interruptState = false;

    ~CoroutineThread();

    CoroutineThread(JNIEnv *env, jobject thiz);

    void run();
};

#endif //COROUTINE_THREAD_H
