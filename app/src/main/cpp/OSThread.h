//
// Created by zhangtao on 2022/2/11.
//

#ifndef COROUTINE_OSTHREAD_H
#define COROUTINE_OSTHREAD_H


#include "CoroutineDespatcher.h"

class OSThread {
public:
    long threadId;
    CoroutineDespatcher *despatcher;

    OSThread(JNIEnv *env, long threadId);

    ~OSThread();

    void start();

    static void *thread_entry_function(void *args);
};


#endif //COROUTINE_OSTHREAD_H
