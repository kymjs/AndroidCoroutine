//
// Created by zhangtao on 2022/2/11.
//

#ifndef COROUTINE_THREAD_H
#define COROUTINE_THREAD_H

#include <jni.h>
#include "ConcurrenceQueue.h"
#include "pthread.h"
#include "OSCoroutine.h"
#include "log.h"

class CoroutineDespatcher {
private:
    ConcurrenceQueue<OSCoroutine *> fightQueue;
    ConcurrenceQueue<OSCoroutine *> suspendQueue;
    OSCoroutine *fightCoroutine;
    bool mainThread;
    JNIEnv *env;

    void despatchInMainThread(OSCoroutine *pCoroutine);

public:
    JavaVM *jvm;

    ~CoroutineDespatcher();

    CoroutineDespatcher(JNIEnv *env, bool mainThread);

    void despatch();

    void join(jobject jobj);

    void attachCoroutine(jobject jobj);
};

#endif //COROUTINE_THREAD_H
