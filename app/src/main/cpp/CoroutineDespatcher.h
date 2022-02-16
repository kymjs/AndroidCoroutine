//
// Created by zhangtao on 2022/2/11.
//

#ifndef COROUTINE_THREAD_H
#define COROUTINE_THREAD_H

#include <jni.h>
#include "ConcurrenceQueue.h"
#include "Suspender.h"
#include "OSCoroutine.h"
#include "log.h"

using namespace std;

class CoroutineDespatcher {
private:
    ConcurrenceQueue<OSCoroutine *> queue;
    bool mainThread;
    JNIEnv *env;

    void despatchInMainThread(OSCoroutine *pCoroutine);

public:
    JavaVM *jvm;
    Suspender parker;
    bool interruptState = false;

    ~CoroutineDespatcher();

    CoroutineDespatcher(JNIEnv *env, bool mainThread);

    void despatch();

    void attachCoroutine(jobject jobj);
};

#endif //COROUTINE_THREAD_H
