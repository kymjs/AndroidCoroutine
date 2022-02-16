//
// Created by zhangtao on 2022/2/11.
//

#include "CoroutineDespatcher.h"

CoroutineDespatcher::CoroutineDespatcher(JNIEnv *env, bool mainThread) {
    env->GetJavaVM(&(this->jvm));
    this->mainThread = mainThread;
    this->env = env;
}

CoroutineDespatcher::~CoroutineDespatcher() {
    jvm->DetachCurrentThread();
}

void CoroutineDespatcher::despatchInMainThread(OSCoroutine *pCoroutine) {
    if (pCoroutine != nullptr) {
        pCoroutine->async(env);
        delete pCoroutine;
    }
}

void CoroutineDespatcher::despatch() {
    while (!mainThread) {
        LOGD("========准备获取队列中的协程");
        OSCoroutine *pCoroutine = queue.pop();
        LOGD("========执行协程%lld", pCoroutine->coroutineId);
        pCoroutine->async(env);
        delete pCoroutine;
    }
}

void CoroutineDespatcher::attachCoroutine(jobject jobj) {
    if (mainThread) {
        despatchInMainThread(new OSCoroutine(env, jobj));
    } else {
        queue.push(new OSCoroutine(env, jobj));
    }
}
