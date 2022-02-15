//
// Created by zhangtao on 2022/2/11.
//

#include "log.h"
#include "OSThread.h"

OSThread::OSThread(CoroutineThread *pCoroutineThread) {
    this->coroutineThread = pCoroutineThread;
}

void OSThread::start() {
    pthread_t tid;
    pthread_attr_t Attr;
    pthread_attr_init(&Attr);
    pthread_attr_setdetachstate(&Attr, PTHREAD_CREATE_DETACHED);
    if (pthread_create(&tid, &Attr, &OSThread::thread_entry_function, this->coroutineThread) != 0) {
        LOGD("create thread error");
        return;
    }
    LOGD("started a thread tid=%ld", tid);
    pthread_attr_destroy(&Attr);
}

void *OSThread::thread_entry_function(void *args) {
    CoroutineThread *pCoroutineThread = static_cast<CoroutineThread *>(args);
    pCoroutineThread->run();
    delete pCoroutineThread;
}
