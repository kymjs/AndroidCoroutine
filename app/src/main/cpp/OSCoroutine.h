//
// Created by zhangtao on 2022/2/14.
//

#ifndef COROUTINE_OSCOROUTINE_H
#define COROUTINE_OSCOROUTINE_H


#include <jni.h>
#include "log.h"

class OSCoroutine {
public:
    JavaVM *jvm;
    jobject jCoroutine;
    jlong coroutineId;
    bool suspendState = false;

    ~OSCoroutine();

    OSCoroutine(JNIEnv *env, jobject thiz);

    void async(JNIEnv *env);

    void await(JNIEnv *env, jobject result);

    void delay(jlong millis);
};


#endif //COROUTINE_OSCOROUTINE_H
