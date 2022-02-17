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
        if (suspendQueue.empty()) {
            fightCoroutine = fightQueue.pop();
            if (fightCoroutine->suspendState == NONE) {
                LOGD("====fightQueue->执行协程%lld", fightCoroutine->coroutineId);
                fightCoroutine->async(env);
                if (fightCoroutine->suspendState == FINISHED) {
                    delete fightCoroutine;
                }
            }
        } else {
            if (suspendQueue.try_pop(fightCoroutine)) {
                if (fightCoroutine->suspendState < RESUMED) {
                    LOGD("====suspendQueue->执行协程%lld", fightCoroutine->coroutineId);
                    fightCoroutine->async(env);
                }

                if (fightCoroutine->suspendState == FINISHED) {
                    delete fightCoroutine;
                }
            }
        }
    }
}

void CoroutineDespatcher::join(jobject jobj) {
    if (mainThread) {
        despatchInMainThread(new OSCoroutine(env, jobj));
    } else {
        if (fightCoroutine != nullptr) {
            fightCoroutine->suspendState = SUSPEND;
            suspendQueue.push_front(fightCoroutine, new OSCoroutine(env, jobj));
        } else {
            suspendQueue.push_front(new OSCoroutine(env, jobj));
        }
    }
}

void CoroutineDespatcher::attachCoroutine(jobject jobj) {
    if (mainThread) {
        despatchInMainThread(new OSCoroutine(env, jobj));
    } else {
        fightQueue.push(new OSCoroutine(env, jobj));
    }
}
