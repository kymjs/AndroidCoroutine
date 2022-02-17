//
// Created by zhangtao on 2022/2/14.
//

#ifndef COROUTINE_OSCOROUTINE_H
#define COROUTINE_OSCOROUTINE_H


#include <jni.h>
#include "log.h"
#include <setjmp.h>

const int NONE = 0;
const int SUSPEND = 1;
const int NEED_RESUME = 2;
const int RESUMED = 3;
const int FINISHED = 4;

class OSCoroutine {
private:
    jmp_buf suspendPoint;
public:
    JavaVM *jvm;
    jobject jCoroutine;
    jlong coroutineId;
    int suspendState = NONE;

    ~OSCoroutine();

    OSCoroutine(JNIEnv *env, jobject thiz);

    void async(JNIEnv *env);

    void await(JNIEnv *env, jobject result);

    void suspendAwait(JNIEnv *env, jobject result);

    void delay(jlong millis);

    void resume(JNIEnv *env);
};


#endif //COROUTINE_OSCOROUTINE_H
