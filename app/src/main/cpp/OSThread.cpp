//
// Created by zhangtao on 2022/2/11.
//

#include "log.h"
#include "OSThread.h"

OSThread::OSThread(JNIEnv *env, long threadId) {
    this->threadId = threadId;
    this->despatcher = new CoroutineDespatcher(env, threadId == 1);
}

OSThread::~OSThread() {
    delete despatcher;
}

void OSThread::start() {
    if (threadId == 1) {
        LOGD("在主线程执行协程");
        despatcher->despatch();
    } else {
        pthread_t tid;
        pthread_attr_t Attr;
        pthread_attr_init(&Attr);
        pthread_attr_setdetachstate(&Attr, PTHREAD_CREATE_DETACHED);
        if (pthread_create(&tid, &Attr, &OSThread::thread_entry_function, this->despatcher) != 0) {
            LOGD("线程创建失败");
            return;
        }
        LOGD("启动C线程 tid=%ld", tid);
        pthread_attr_destroy(&Attr);
    }
}

void *OSThread::thread_entry_function(void *args) {
    auto *despatcher = static_cast<CoroutineDespatcher *>(args);
    despatcher->despatch();
    delete despatcher;
}
