//
// Created by zhangtao on 2022/2/11.
//

#ifndef COROUTINE_OSTHREAD_H
#define COROUTINE_OSTHREAD_H


#include "CoroutineThread.h"

class OSThread {
private:
    CoroutineThread *coroutineThread;

public:
    OSThread(CoroutineThread *pCoroutineThread);

    void start();

    static void *thread_entry_function(void *args);
};


#endif //COROUTINE_OSTHREAD_H
